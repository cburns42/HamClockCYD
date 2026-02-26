/*
 * Using library lvgl at version 9.4.0
 * Using library TFT_eSPI at version 2.5.43
 * Using library SPI at version 3.3.7
 * Using library FS at version 3.3.7
 * Using library SPIFFS at version 3.3.7
 * Using library XPT2046_Touchscreen at version 1.4
 * Using library ArduinoJson at version 7.4.2
 * Using library SparkFun BME280 at version 2.0.11
 * Using library Wire at version 3.3.7
 * Using library WiFi at version 3.3.7
 * Using library Networking at version 3.3.7
 * Using library Time at version 1.6.1
 * Using library sunMoon-master
 * Using library DS3232RTC at version 3.1.2
 * Using library Preferences at version 3.3.7
 * Using library HTTPClient at version 3.3.7
 * Using library NetworkClientSecure at version 3.3.7
 * Using library Async TCP at version 3.4.10
 * Using library ESP Async WebServer at version 3.10.0
 * Using library Hash at version 3.3.7
 */

#include <lvgl.h>
#include "screens.h"
#include "ui.h"
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <ArduinoJson.h>
#include "SparkFunBME280.h"
#include <WiFi.h>
#include <TimeLib.h>
#include <rom/rtc.h>
#include "driver/rtc_io.h"
#include <sunMoon.h>
#include <DS3232RTC.h>
#include "images.h"
#include <Preferences.h>
#include <string.h>
#include <stdlib.h>
#include <tinyxml2.h>
#include "solarXML.h"
#include "weatherJSON.h"
#include <HTTPClient.h>

Preferences prefs;
boolean prefsNeedsUpdate = false;

#define CYD_LED_RED   4
#define CYD_LED_GREEN 16
#define CYD_LED_BLUE  17
#define CYD_BACKLIGHT  21

#define TEMPERATURE_F 0
#define TEMPERATURE_C 1

int backLightLevel = 255;

const char * dowS[8] = {"Whatday", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char * monthS[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

const char* ntpServer = "pool.ntp.org";
long  utcOffset_sec   = 0;
long  zone1Offset_sec = -5 * 3600;
long  zone2Offset_sec = -7 * 3600;
const int   daylightOffset_sec = 3600;


struct tm utcTimeinfo, zone1Timeinfo, zone2Timeinfo;
struct tm *s_UTC;
struct tm *zone1TM;
struct tm *zone2TM;
sunMoon sm;
double sunrise, sunset;
time_t sRise;
time_t sSet;
int prevHour, prevMinute;

const double latitude = 43.122497;
const double longitude = -71.918434;

/*
 * Loop count used when connecting to WiFi, Loop will attempt, wait 10ms and try again
 */
#define WIFICONNECTCOUNT 600
/// HTTP client errors
const char * httpClientErrorS[12] = {"UNKNOWN ERROR",
                                     "CONNECTION REFUSED (-1)",
                                     "SEND HEADER FAILED (-2)",
                                     "SEND PAYLOAD FAILED (-3)",
                                     "NOT CONNECTED (-4)",
                                     "CONNECTION LOST (-5)",
                                     "NO STREAM (-6)",
                                     "NO HTTP SERVER (-7)",
                                     "NO RAM (-8)",
                                     "ENCODING (-9)",
                                     "STREAM WRITE (-10)",
                                     "READ TIMEOUT (-11)"
};

/*
 * Timeouts for API connections in milliseconds
 */
#define WIFIWEATHERTMO 6000
#define WIFIWEATHERCONNECTTMO 3000
#define WIFISOLARTMO 10000
#define WIFISOLARCONNECTTMO 3000

char ssid_value[64] = "";
char password_value[64] = "";
char openweather_key_value[128] = "";
double openweather_latitude = 0.0;
double openweather_longitude = 0.0;

char solarBuffer[2048];
char weatherBuffer[2048];

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33
SPIClass touchscreenSpi = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
uint16_t touchScreenMinimumX = 200, touchScreenMaximumX = 3700, touchScreenMinimumY = 240, touchScreenMaximumY = 3800;
BME280 bme280;
DS3232RTC RTClock;

#define TFT_HOR_RES 240
#define TFT_VER_RES 320

#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))

/*
 * Function reads touchscreen and maps to display coordinates
 */
void touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
  if (touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();

    if (p.x < touchScreenMinimumX) touchScreenMinimumX = p.x;
    if (p.x > touchScreenMaximumX) touchScreenMaximumX = p.x;
    if (p.y < touchScreenMinimumY) touchScreenMinimumY = p.y;
    if (p.y > touchScreenMaximumY) touchScreenMaximumY = p.y;
    //Map this to the pixel position
    data->point.x = map(p.x, touchScreenMinimumX, touchScreenMaximumX, 1, TFT_HOR_RES); /* Touchscreen X calibration */
    data->point.y = map(p.y, touchScreenMinimumY, touchScreenMaximumY, 1, TFT_VER_RES); /* Touchscreen Y calibration */
    data->state = LV_INDEV_STATE_PRESSED;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

/*
 * Function to extract time zone 1 (home zone) Tools tab UI settings
 * Update Clock tab display
 * Update value used for time zone 1 calculations
 * Set flag to indicate perferences need to be saved.
 */
void updateZone1(){
  int16_t zoneValue;
  char zoneBuffer[32];

  lv_dropdown_get_selected_str(objects.zone1_dropdown, zoneBuffer, sizeof(zoneBuffer));
  lv_label_set_text(objects.zone1_text_label, zoneBuffer);
  zoneValue = atoi(zoneBuffer);
  zone1Offset_sec = (zoneValue * 3600);
  prefsNeedsUpdate = true;
}

/*
 * Function to extract time zone 2 (home zone) Tools tab UI settings
 * Update Clock tab display
 * Update value used for time zone 2 calculations
 * Set flag to indicate perferences need to be saved.
 */
void updateZone2(){
  int16_t zoneValue;
  char zoneBuffer[32];

  lv_dropdown_get_selected_str(objects.zone2_dropdown, zoneBuffer, sizeof(zoneBuffer));
  lv_label_set_text(objects.zone2_text_label, zoneBuffer);
  zoneValue = atoi(zoneBuffer);
  zone2Offset_sec = (zoneValue * 3600);
  prefsNeedsUpdate = true;
}


/*
 * Event handling for Tools tab timezone dropdowns
 */
void zone_dropdown_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = (lv_obj_t * )lv_event_get_target(e);

  if(code == LV_EVENT_VALUE_CHANGED) {
    if(obj == objects.zone1_dropdown){
      updateZone1();
    }

    if(obj == objects.zone2_dropdown){
      updateZone2();
    }
  }
}

/*
 * Event handling for Tools tab brightness setting
 * Set flag to indicate perferences need to be saved.
 */
void action_brightness_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_RELEASED) {
    setBrightness(lv_slider_get_value(objects.brightness_slider));
    prefsNeedsUpdate = true;
  }
}

/*
 * Event handling for Tools tab text entry settings. This occurs when the enter key 
 * is pressed on a virtual keyboard. The primary use is for entering user Callsign.
 * Set flag to indicate perferences need to be saved.
 */
static void textarea_event_handler(lv_event_t * e) {
	lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * target = (lv_obj_t * )lv_event_get_current_target(e);

    if (code == LV_EVENT_FOCUSED) {
		lv_obj_clear_flag(objects.tools_entry_panel, LV_OBJ_FLAG_HIDDEN);
		lv_keyboard_set_textarea(objects.tools_keyboard, target);
		lv_keyboard_set_textarea(objects.tools_keyboard, target);
    } else if (code == LV_EVENT_READY || code == LV_EVENT_INSERT) {
        lv_obj_add_flag(objects.tools_entry_panel, LV_OBJ_FLAG_HIDDEN);
        lv_keyboard_set_textarea(objects.tools_keyboard, NULL);
        prefsNeedsUpdate = true;
    }
}

lv_indev_t *indev;      //Touchscreen input device
uint8_t *draw_buf;      //draw_buf is allocated on heap otherwise the static area is too big on ESP32 at compile
uint32_t lastTick = 0;  //Used to track the tick timer

/*
 * Function is called to set the PWM configured to drive the display backlight.
 */
void setBrightness(int level) {
  level = constrain(level, 0, 255);
  ledcWrite(CYD_BACKLIGHT, level);
  backLightLevel = level;
}

/*
 * Function to extract configuration settings from the Tools tab
 * Change Clock tab display icons based on settings
 * for Optional Tabs; Solar Conditions and Weather show or hide display elements on those tabs
 */
void updateEnables(){
  boolean wifiEnabled, clockUpdateEnabled, solarUpdateEnabled, weatherUpdateEnabled;

  wifiEnabled =          lv_obj_has_state(objects.wifi_enable_checkbox, LV_STATE_CHECKED);
  clockUpdateEnabled =   lv_obj_has_state(objects.wifi_time_checkbox, LV_STATE_CHECKED);
  solarUpdateEnabled =   lv_obj_has_state(objects.wifi_solar_checkbox, LV_STATE_CHECKED);
  weatherUpdateEnabled = lv_obj_has_state(objects.wifi_weather_checkbox, LV_STATE_CHECKED);

  if(wifiEnabled){
    lv_obj_clear_flag(objects.wifi_enable_img, LV_OBJ_FLAG_HIDDEN);
    if(clockUpdateEnabled){
      lv_obj_clear_flag(objects.time_enable_img, LV_OBJ_FLAG_HIDDEN);
    } else {
      lv_obj_add_flag(objects.time_enable_img, LV_OBJ_FLAG_HIDDEN);
    }
    if(solarUpdateEnabled){
      lv_obj_clear_flag(objects.solar_enable_img, LV_OBJ_FLAG_HIDDEN);

      lv_obj_clear_flag(objects.vhf_conditions_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(objects.solar_conditions_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(objects.calculated_conditions_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(objects.last_update_panel, LV_OBJ_FLAG_HIDDEN);
    } else {
      lv_obj_add_flag(objects.solar_enable_img, LV_OBJ_FLAG_HIDDEN);

      lv_obj_add_flag(objects.vhf_conditions_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.solar_conditions_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.calculated_conditions_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.last_update_panel, LV_OBJ_FLAG_HIDDEN);
    }
    if(weatherUpdateEnabled){
      lv_obj_clear_flag(objects.weather_enable_img, LV_OBJ_FLAG_HIDDEN);

      lv_obj_clear_flag(objects.now_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(objects.now_description_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(objects.wind_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(objects.today_panel, LV_OBJ_FLAG_HIDDEN);
    } else {
      lv_obj_add_flag(objects.weather_enable_img, LV_OBJ_FLAG_HIDDEN);

      lv_obj_add_flag(objects.now_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.now_description_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.wind_panel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.today_panel, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_remove_state(objects.wifi_time_checkbox, LV_STATE_DISABLED);
    lv_obj_remove_state(objects.wifi_solar_checkbox, LV_STATE_DISABLED);
    lv_obj_remove_state(objects.wifi_weather_checkbox, LV_STATE_DISABLED);
  } else {
    lv_obj_add_flag(objects.wifi_enable_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.time_enable_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.solar_enable_img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.weather_enable_img, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_state(objects.wifi_time_checkbox, LV_STATE_DISABLED);
    lv_obj_add_state(objects.wifi_solar_checkbox, LV_STATE_DISABLED);
    lv_obj_add_state(objects.wifi_weather_checkbox, LV_STATE_DISABLED);
  }
}

/*
 * Function to read saved preferences from non volatile memory
 * Update variables and UI elements 
 */
void prefsGet(){
  char returnedBuf[128];
  size_t len;

  prefs.begin("HamClock", false);

  len = prefs.getString("prefCallsign", returnedBuf, 32); 
  lv_label_set_text(objects.callsign_display_label, returnedBuf);
  lv_textarea_set_text(objects.callsign_textarea, returnedBuf);

  len = prefs.getString("prefSSID", returnedBuf, 32);
  strcpy(ssid_value, returnedBuf);

  len = prefs.getString("prefPassword", returnedBuf, 32); 
  strcpy(password_value, returnedBuf);

  len = prefs.getString("perfOWKey", returnedBuf, 128); 
  strcpy(openweather_key_value, returnedBuf);

  openweather_latitude = prefs.getDouble("perfOWLat");
  openweather_longitude = prefs.getDouble("perfOWLon");

  lv_dropdown_set_selected(objects.zone1_dropdown, prefs.getInt("prefZone1"));
  lv_dropdown_set_selected(objects.zone2_dropdown, prefs.getInt("prefZone2"));

  lv_slider_set_value(objects.brightness_slider, prefs.getInt("prefBrightness"), false);

  lv_obj_add_state(objects.wifi_time_checkbox,    (lv_state_t)prefs.getBool("prefTimeEnable"));
  lv_obj_add_state(objects.wifi_solar_checkbox,   (lv_state_t)prefs.getBool("prefSolarEnable"));
  lv_obj_add_state(objects.wifi_weather_checkbox, (lv_state_t)prefs.getBool("prefOWEnable"));
  lv_obj_add_state(objects.wifi_enable_checkbox,  (lv_state_t)prefs.getBool("prefWiFiEnable"));

  prefs.end();
  updateEnables();
}

/*
 * Function to save preferences to non volatile memory
 * From variables and UI elements 
 */
void prefsPut(){
  if(prefsNeedsUpdate){
    prefsNeedsUpdate = false;
    prefs.begin("HamClock", false);
    prefs.putString("prefCallsign",    lv_textarea_get_text(objects.callsign_textarea));
    prefs.putString("prefSSID",        ssid_value);
    prefs.putString("prefPassword",    password_value);
    prefs.putString("perfOWKey",       openweather_key_value);
    prefs.putDouble("perfOWLat",       openweather_latitude);
    prefs.putDouble("perfOWLon",       openweather_longitude);
    prefs.putInt(   "prefZone1",       lv_dropdown_get_selected(objects.zone1_dropdown));
    prefs.putInt(   "prefZone2",       lv_dropdown_get_selected(objects.zone2_dropdown));
    prefs.putInt(   "prefBrightness",  lv_slider_get_value(objects.brightness_slider));
    prefs.putBool(  "prefTimeEnable",  lv_obj_has_state(objects.wifi_time_checkbox, LV_STATE_CHECKED));
    prefs.putBool(  "prefSolarEnable", lv_obj_has_state(objects.wifi_solar_checkbox, LV_STATE_CHECKED));
    prefs.putBool(  "prefOWEnable",    lv_obj_has_state(objects.wifi_weather_checkbox, LV_STATE_CHECKED));
    prefs.putBool(  "prefWiFiEnable",  lv_obj_has_state(objects.wifi_enable_checkbox, LV_STATE_CHECKED));

    prefs.end();
  }
}

/*
 * This function will get called if WiFi us enabled, and Weather is enabled. It is called every 10 minutes.
 * The function makes an Open weather API call which fetches a JSON payload with is stored in a buffer
 * This is done so that even if a call fails the previous version is available for display.
 */
void fetchWeather(){
  char jsonUrl[256];
  char buf2[32];

  if(startWiFi()){
    lv_dropdown_get_selected_str(objects.temperature_dropdown, buf2, sizeof(buf2));
    sprintf(jsonUrl, "https://api.openweathermap.org/data/2.5/weather?lat=%f&lon=%f&appid=%s&units=%s", 
                     openweather_latitude,
                     openweather_longitude,
                     openweather_key_value,
                     buf2
    );

    HTTPClient http;
    Serial.println("In fetchWeather, WiFi connected");
    http.begin(jsonUrl);

    http.setConnectTimeout(WIFIWEATHERCONNECTTMO);
    http.setTimeout(WIFIWEATHERTMO);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString(); // Get the response payload
      payload.toCharArray(weatherBuffer, payload.length()+1);
      lv_image_set_src(objects.weather_enable_img, &img_weather_24);

    } else {
      lv_image_set_src(objects.weather_enable_img, &img_weather_alert_24);
      Serial.print("In fetchWeather, response Failed: "); printhttpResponseCode(httpResponseCode);
    }

    stopWiFi();
  } else {
    Serial.println("In fetchWeather, WiFi Failed to connect");
  }
}

/*
 * This function will get called if WiFi us enabled, and Solar is enabled. It is called every 3 hours.
 * The function makes an API call to n0nbh and fetches a XML payload with is stored in a buffer
 * This is done so that even if a call fails the previous version is available for display.
 */
void fetchSolar(){

  if(startWiFi()){
    HTTPClient http;
    Serial.println("In fetchSolar, WiFi connected");
    http.begin("https://www.hamqsl.com/solarxml.php"); // Specify the URL
    http.addHeader("Accept", "application/xml"); // Request XML format

    http.setConnectTimeout(WIFISOLARCONNECTTMO);
    http.setTimeout(WIFISOLARTMO);

    int httpResponseCode = http.GET(); // Send the HTTP GET request

    if (httpResponseCode > 0) {
      String payload = http.getString(); // Get the response payload
      payload.toCharArray(solarBuffer, payload.length()+1);
      lv_image_set_src(objects.solar_enable_img, &img_solar_24);
    } else {
      Serial.print("In fetchSolar, response Failed: "); printhttpResponseCode(httpResponseCode);
      lv_image_set_src(objects.solar_enable_img, &img_solar_alert_24);
    }

    stopWiFi();
  } else {
    Serial.println("In fetchSolar, WiFi Failed to connect");
  }
}


void printhttpResponseCode(int code){
  Serial.print(code);
  Serial.print(": ");
  if(code > 0){
    Serial.print(code);
    Serial.println("HTTP codes see RFC7231");
  }
  if(code <= 0){
    if((code == 0) || (code < -11)){
      Serial.println(httpClientErrorS[0]); // Unknown error
    } else {
      Serial.println(httpClientErrorS[abs(code)]);
    }
  }
}

/*
 * This function is called if WiFi is enabled and any of the functions that uses WiFi needs an update
 * This includes Time sync (every 25 hours), Weather (every 10 minutes), Solar conditions (every 10 minutes).
 * It updates Clock tab WiFi icon; Red until connected (or error)), Black when connected.
 */
boolean startWiFi(){
  int wait_count = 0;

  WiFi.begin(ssid_value, password_value);
  while ((WiFi.status() != WL_CONNECTED) && wait_count < WIFICONNECTCOUNT) {
    wait_count++;
    lv_image_set_src(objects.wifi_enable_img, &img_wifi_alert_24);
    lv_timer_handler();
    delay(10);
  }
  if(wait_count < WIFICONNECTCOUNT){
    lv_image_set_src(objects.wifi_enable_img, &img_wifi_on_24);
    lv_timer_handler();
    return(true);
  } else {
    return(false);
  }
}

/*
 * This function is called after another function has used WiFi. 
 * It closes the WiFi connection and updates 
 * It updates Clock tab WiFi icon to gray to indicate that it is enabled but not connected
 */
void stopWiFi(){
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  lv_image_set_src(objects.wifi_enable_img, &img_wifi_off_24);
  lv_timer_handler();
}

/*
 * This function is called every 24 hours if WiFi and Time Sync are enabled
 * Call connects to an NTP server to fetch time and update the RTC
 */
void fetchTime(void){
  struct tm timeinfo;
  time_t currentTime;

  if(startWiFi()){
    Serial.println("In fetchTime, WiFi connected");
    configTime(utcOffset_sec, daylightOffset_sec, ntpServer);
    if(!getLocalTime(&timeinfo)){
      return;
      Serial.println("In fetchTime, response failed");
    }

    time(&currentTime);
    RTClock.set(currentTime);

    stopWiFi();
  } else {
    Serial.println("In fetchTime, WiFi failed to connect");
  }
}

/*
 * This function is called if the user has closed the UI dialog used for
 * manually entering time and date and updates the RTC.
 */
static void settings_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  char buf[8];
  int hours, minutes, seconds;

  if(code == LV_EVENT_CLICKED) {
    lv_obj_set_flag(objects.settings_panel,LV_OBJ_FLAG_HIDDEN,true);
    lv_calendar_date_t date;
    lv_calendar_get_pressed_date(objects.date_setting_calendar, &date);

    lv_dropdown_get_selected_str(objects.tens_hours_dropdown, buf, sizeof(buf));
    hours = atoi(buf) * 10;
    lv_dropdown_get_selected_str(objects.hours_dropdown, buf, sizeof(buf));
    hours = hours + atoi(buf);

    lv_dropdown_get_selected_str(objects.tens_min_dropdown, buf, sizeof(buf));
    minutes = atoi(buf) * 10;
    lv_dropdown_get_selected_str(objects.min_dropdown, buf, sizeof(buf));
    minutes = minutes + atoi(buf);

    lv_dropdown_get_selected_str(objects.tens_sec_dropdown, buf, sizeof(buf));
    seconds = atoi(buf) * 10;
    lv_dropdown_get_selected_str(objects.sec_dropdown, buf, sizeof(buf));
    seconds = seconds + atoi(buf);
    setTime(hours, minutes, seconds, date.day, date.month, date.year);
    RTClock.set(now());
  }
}

/*
 * This function is called if the user has closed the UI dialog used for
 * manually entering time and date but cancels.
 */
static void cancel_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_CLICKED) {
    lv_obj_set_flag(objects.settings_panel,LV_OBJ_FLAG_HIDDEN,true);
  }
}

/*
 * This function is called when the user selects the WiFi settings on the Tools tab
 * It updates Clock page status icons
 * Most significanly is calls a function that Starts an WiFi Access Point, starts a 
 * Web server used to collect settings for WiFi, and Open Weather settings that 
 * are too difficult to enter on a tiny virtual keyboard.
 */
static void WiFi_Btn_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_CLICKED) {
    lv_obj_remove_flag(objects.wifi_message_label, LV_OBJ_FLAG_HIDDEN);
    settings_ap_setup();
  }
}

/*
 * This function is called with the user clicks the Manual Set Time button on the Tools Tab
 * This makes the entry fields visable (normally hidden), and sets an inial value to the
 * calendar to make it easier for the user.
 */
static void Timeset_Btn_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_CLICKED) {
    lv_obj_set_flag(objects.settings_panel, LV_OBJ_FLAG_HIDDEN, false);
    lv_calendar_set_showed_date(objects.date_setting_calendar, ((zone1TM->tm_year)-100)+2000, (zone1TM->tm_mon)+1);
  }
}

/*
 * This fuction is called when the user clicks the WiFi Time Sync checkbox on the Tools Tab
 * It calls the updateEnables function, and also sets a global variable to indicate user preferences
 * need to be updated.
 */
static void wifi_time_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_VALUE_CHANGED) {
    prefsNeedsUpdate = true;
    updateEnables();
  }
}

/*
 * This fuction is called when the user clicks the WiFi Solar checkbox on the Tools Tab
 * It calls the updateEnables function, and also sets a global variable to indicate user preferences
 * need to be updated.
 */
static void wifi_solar_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_VALUE_CHANGED) {
    prefsNeedsUpdate = true;
    updateEnables();
  }
}

/*
 * This fuction is called when the user clicks the WiFi Weather checkbox on the Tools Tab
 * It calls the updateEnables function, and also sets a global variable to indicate user preferences
 * need to be updated.
 */
static void wifi_weather_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_VALUE_CHANGED) {
    prefsNeedsUpdate = true;
    updateEnables();
  }
}

/*
 * This fuction is called when the user clicks the Clear Settings button on the Tools tab
 * It calls the updateEnables function, and also sets a global variable to indicate user preferences
 * need to be updated.
 */
static void wifi_enable_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);

  if(code == LV_EVENT_VALUE_CHANGED) {
    prefsNeedsUpdate = true;
    updateEnables();
  }
}

/*
 * This fuction is called when the user clicks the WiFi enable checkbox
 * This will remove all user preferences.
 */
void clearPerfs(){
  prefs.begin("HamClock", false);
  prefs.clear();
  prefs.end();
}

/*
 * Arduino entry point. This function will:
 * Set up I/O pins for the application
 * Start I2C devices; RTC and Weather sensor
 * Initialize Touchscreen
 * Initialize the Display
 * Load initial values for Tab displays
 * Initilize UI and UI event handlers
 * Read and/or Initilize user preferences
 */
void setup() {
  Serial.begin(115200);
  pinMode(CYD_LED_RED,   OUTPUT); digitalWrite(CYD_LED_RED,   1);
  pinMode(CYD_LED_GREEN, OUTPUT); digitalWrite(CYD_LED_GREEN, 1);
  pinMode(CYD_LED_BLUE,  OUTPUT); digitalWrite(CYD_LED_BLUE,  1);
  pinMode(CYD_BACKLIGHT,  OUTPUT);

  ledcAttach(CYD_BACKLIGHT, 5000, 8);
  ledcWrite(CYD_BACKLIGHT, 150);
  setBrightness(150);

  Wire.begin(22, 27);
  bme280.setI2CAddress(0x76);
  bme280.beginI2C();
  RTClock.begin();

  //Initialise the touchscreen
  touchscreenSpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSpi);
  touchscreen.setRotation(2);

  //Initialise LVGL GUI
  lv_init();

  draw_buf = new uint8_t[DRAW_BUF_SIZE];
  lv_display_t *disp;
  disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, DRAW_BUF_SIZE);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);

  //Initialize the touchscreen input device driver
  indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touchpad_read);

//Init Solar/Weather data with sample data
  strncpy(solarBuffer, testDocument, strlen(testDocument));
  strncpy(weatherBuffer, testJSON, strlen(testJSON));

  ui_init();
  lv_obj_set_flag(objects.settings_panel,LV_OBJ_FLAG_HIDDEN,true);
  lv_obj_set_flag(objects.tools_entry_panel,LV_OBJ_FLAG_HIDDEN,true);
  lv_obj_add_flag(objects.wifi_message_label, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_event_cb(objects.brightness_slider, action_brightness_event_handler, LV_EVENT_RELEASED, (void *)0);

  lv_obj_add_event_cb(objects.tools_keyboard, textarea_event_handler, LV_EVENT_READY, (void *)0);

  lv_obj_add_event_cb(objects.callsign_textarea, textarea_event_handler, LV_EVENT_FOCUSED, (void *)0);
  lv_obj_add_event_cb(objects.manual_set_button, Timeset_Btn_event_handler, LV_EVENT_CLICKED, (void *)0);
  lv_obj_add_event_cb(objects.wifi_set_button, WiFi_Btn_event_handler, LV_EVENT_CLICKED, (void *)0);
  lv_obj_add_event_cb(objects.zone1_dropdown, zone_dropdown_event_handler, LV_EVENT_VALUE_CHANGED, (void *)0);
  lv_obj_add_event_cb(objects.zone2_dropdown, zone_dropdown_event_handler, LV_EVENT_VALUE_CHANGED, (void *)0);

  lv_obj_add_event_cb(objects.wifi_time_checkbox, wifi_time_event_handler, LV_EVENT_VALUE_CHANGED, (void *)0);
  lv_obj_add_event_cb(objects.wifi_solar_checkbox, wifi_solar_event_handler, LV_EVENT_VALUE_CHANGED, (void *)0);
  lv_obj_add_event_cb(objects.wifi_weather_checkbox, wifi_weather_event_handler, LV_EVENT_VALUE_CHANGED, (void *)0);
  lv_obj_add_event_cb(objects.wifi_enable_checkbox, wifi_enable_event_handler, LV_EVENT_VALUE_CHANGED, (void *)0);
  lv_obj_add_event_cb(objects.save_settings_button, settings_event_handler, LV_EVENT_CLICKED, (void *)0);
  lv_obj_add_event_cb(objects.cancel_settings_button, cancel_event_handler, LV_EVENT_CLICKED, (void *)0);

  char intialVal[32] = "Initial";

  prefs.begin("HamClock", false);
  if (not prefs.isKey("prefCallsign")) {
    lv_textarea_set_text(objects.callsign_textarea, intialVal);
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("prefSSID")) {
    strcpy(ssid_value, intialVal);
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("prefPassword")) {
    strcpy(password_value, intialVal);
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("perfOWKey")) {
    strcpy(openweather_key_value, intialVal);
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("perfOWLat")) {
    openweather_latitude = 0.0;
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("perfOWLon")) {
    openweather_longitude = 0.0;
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("prefZone1")) {
    lv_dropdown_set_selected(objects.zone1_dropdown, -5);
    updateZone1();
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("prefZone2")) {
    lv_dropdown_set_selected(objects.zone2_dropdown, -4);
    updateZone2();
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("prefBrightness")) {
    lv_slider_set_value(objects.brightness_slider, 255, false);
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("prefTimeEnable")) {
    lv_obj_remove_state(objects.wifi_time_checkbox, LV_STATE_CHECKED);
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("prefSolarEnable")) {
    lv_obj_remove_state(objects.wifi_solar_checkbox, LV_STATE_CHECKED);
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("prefOWEnable")) {
    lv_obj_remove_state(objects.wifi_weather_checkbox, LV_STATE_CHECKED);
    prefsNeedsUpdate = true;
  }
  if (not prefs.isKey("prefWiFiEnable")) {
    lv_obj_remove_state(objects.wifi_enable_checkbox, LV_STATE_CHECKED);
    prefsNeedsUpdate = true;
  }

  prefs.end();
  if(prefsNeedsUpdate){
    prefsPut();
  } else {
    prefs.end();
    prefsGet();
    updateZone1();
    updateZone2();
    setBrightness(lv_slider_get_value(objects.brightness_slider));
    lv_label_set_text(objects.callsign_display_label, lv_textarea_get_text(objects.callsign_textarea));
  }
  updateTimeInfo();
  updateSeconds();
  updateDates();
  updateTimes();
  updateSensors();
}

/*
 * Arduino function called forever
 * Updates UI timed
 * Invokes Screens
 */
void loop() {
  for(int i=0; i < 100; i++){
    lv_tick_inc(millis() - lastTick);
    lastTick = millis();
    lv_timer_handler();
    delay(10);
  }
  updateScreen();
}

/*
 * Function to get data from RTC, set up values for UTC, Timezone 1, Timezone2
 * Calculates Sunrise/Sunset for Zone 1
 */
void updateTimeInfo(){
  time_t rawtime, tmp, tmp2;

  rawtime = RTClock.get();

  s_UTC = gmtime_r (&rawtime, &utcTimeinfo);

  tmp = rawtime + zone1Offset_sec;
  zone1TM = gmtime_r(&tmp, &zone1Timeinfo);

  tmp2 = rawtime + zone2Offset_sec;
  zone2TM = gmtime_r(&tmp2, &zone2Timeinfo);

  sm.init(-300, latitude, longitude);
  time_t s_date;
  time(&s_date);

  time_t testRTC = RTClock.get();

  sRise = sm.sunRise(s_date);
  sSet  = sm.sunSet(s_date);
}

/*
 * Function to get data from temperature sensor, called every 10 minutes
 * Updates Clock Tab display fields
 */
void updateSensors(){
  double temp, hum, press, alti;
  char dispS[32];

  bme280.setMode(MODE_FORCED);
  if(lv_dropdown_get_selected(objects.temperature_dropdown) == TEMPERATURE_F){
    temp = bme280.readTempF();
    lv_image_set_src(objects.temperature_image, &img_temperature_fahrenheit_24);
  } else {
    temp = bme280.readTempC();
    lv_image_set_src(objects.temperature_image, &img_temperature_celsius_24);
  }

  hum = bme280.readFloatHumidity();
  press = (bme280.readFloatPressure() / 100.0);
  alti = bme280.readFloatAltitudeFeet();

  sprintf(dispS, "%03.1f", temp);
  lv_label_set_text(objects.temperature_label, dispS);
  sprintf(dispS, "%03.1f", hum);
  lv_label_set_text(objects.humidity_label, dispS);
  sprintf(dispS, "%04.1f", alti);
  lv_label_set_text(objects.altimeter_label, dispS);
  sprintf(dispS, "%04.1f", press);
  lv_label_set_text(objects.barometer_label, dispS);
}

/*
 * Function updates Clock Tab seconds display fields, called every second
 */
void updateSeconds(){
  char dispS[32];

  sprintf(dispS, ":%02d", s_UTC->tm_sec);
  lv_label_set_text(objects.seconds_time_label, dispS);
}

/*
 * Function to update Clock tab display fields for UTC, Timezone 1, Timezone2
 * Called every minute
 */
void updateTimes(){
  char dispS[32];

  sprintf(dispS, "%02d:%02d", s_UTC->tm_hour, s_UTC->tm_min);
  lv_label_set_text(objects.utc_time_label, dispS);
  sprintf(dispS, "%02d:%02d", zone1TM->tm_hour, zone1TM->tm_min);
  lv_label_set_text(objects.zone1_time_label, dispS);
  sprintf(dispS, "%02d:%02d", zone2TM->tm_hour, zone2TM->tm_min);
  lv_label_set_text(objects.zone2_time_label, dispS);
}

/*
 * Function to update Clock tab display fields for UTC, Timezone 1, Timezone2 Dates
 * Called every hour
 */
void updateDates(){
  char dispS[32];

  sprintf(dispS, "%s %s %02d 20%02d", dowS[s_UTC->tm_wday+1], monthS[s_UTC->tm_mon], s_UTC->tm_mday, s_UTC->tm_year-100);
  lv_label_set_text(objects.utc_date_label, dispS);

  sprintf(dispS, "%s %s %02d 20%02d", dowS[zone1TM->tm_wday+1], monthS[zone1TM->tm_mon], zone1TM->tm_mday, zone1TM->tm_year-100);
  lv_label_set_text(objects.zone1_date_label, dispS);
  
  sprintf(dispS, "%s %s %02d 20%02d", dowS[zone2TM->tm_wday+1], monthS[zone2TM->tm_mon], zone2TM->tm_mday, zone2TM->tm_year-100);
  lv_label_set_text(objects.zone2_date_label, dispS);

  sprintf(dispS, "%02d:%02d",hour(sRise), minute(sRise));
  lv_label_set_text(objects.sunrise_time_label, dispS);
  sprintf(dispS, "%02d:%02d",hour(sSet), minute(sSet));
  lv_label_set_text(objects.sunset_time_label, dispS);
}

using namespace tinyxml2;

/*
 * Function to update Solar tab display fields from parsing XML fetched from fetchSolar function
 * Called every hour
 */
void updateSolarScreen(){
  XMLDocument doc;
  XMLElement* rootElement;
  XMLElement* childElement;
  XMLElement* solarDataElement;
  XMLElement* calcCondElement;
  XMLElement* calcVHFElement;

  XMLError err = doc.Parse(solarBuffer, strlen(solarBuffer));

  if (err != XML_SUCCESS) {
    Serial.print("XML parsing error: "); Serial.println(doc.ErrorIDToName(err));
    return;
  }
  rootElement = doc.RootElement();
  if (rootElement) {
    childElement = rootElement->FirstChildElement("solardata");
    if (childElement) {
      solarDataElement = childElement->FirstChildElement("updated");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.last_updated_txt_label, text);
        }
      }

      solarDataElement = childElement->FirstChildElement("solarflux");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.solar_flux_label, text);
        }
      }

      solarDataElement = childElement->FirstChildElement("aindex");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.aindex_label, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("kindex");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.kindex_label, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("kindexnt");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.kindex_nt_label_1, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("xray");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.xray_label, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("sunspots");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.sunspots_label, text);
        }
      }

      solarDataElement = childElement->FirstChildElement("heliumlin");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.helium_label, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("protonflux");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.proton_flux_label_label, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("electonflux");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.electon_flux_label_label_1, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("aurora");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.aurora_label, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("normalization");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.normalization_label_1, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("solarwind");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.solarwind_label, text);
        }
      }
      solarDataElement = childElement->FirstChildElement("magneticfield");
      if (solarDataElement) {
        const char* text = solarDataElement->GetText();
        if (text) {
          lv_label_set_text(objects.magneticfield_label, text);
        }
      }
      calcCondElement = childElement->FirstChildElement("calculatedconditions");

      int itemCount = 0;
      unsigned int labelColor = 0;
      if (calcCondElement) {
        XMLElement* pBand = calcCondElement->FirstChildElement("band");
        while (pBand != nullptr) {
          const char* itemName = pBand->GetText();
          if (itemName != nullptr) {
            const char* nameValue = pBand->Attribute("name");
            const char* timeValue = pBand->Attribute("time");
            if(strcmp(itemName, "Good") == 0){
                labelColor = 0x006400;
            } else if(strcmp(itemName, "Fair") == 0){
                labelColor = 0xDAD700;
            } else if(strcmp(itemName, "Poor") == 0){
                labelColor = 0xBB0000;
            }
            if(strcmp(nameValue, "80m-40m") == 0){
              if(strcmp(timeValue, "day") == 0){
                lv_label_set_text(objects.m40_80_day_label, itemName);
                lv_obj_set_style_text_color(objects.m40_80_day_label, lv_color_hex(labelColor), 0);
              } else {
                lv_label_set_text(objects.m40_80_night_label, itemName);
                lv_obj_set_style_text_color(objects.m40_80_night_label, lv_color_hex(labelColor), 0);
              }
            } else if(strcmp(nameValue, "30m-20m") == 0){
              if(strcmp(timeValue, "day") == 0){
                lv_label_set_text(objects.m20_30_day_label, itemName);
                lv_obj_set_style_text_color(objects.m20_30_day_label, lv_color_hex(labelColor), 0);
              } else {
                lv_label_set_text(objects.m20_30_night_label, itemName);
                lv_obj_set_style_text_color(objects.m20_30_night_label, lv_color_hex(labelColor), 0);
              }
            } else if(strcmp(nameValue, "17m-15m") == 0){
              if(strcmp(timeValue, "day") == 0){
                lv_label_set_text(objects.m15_17_day_label, itemName);
                lv_obj_set_style_text_color(objects.m15_17_day_label, lv_color_hex(labelColor), 0);
              } else {
                lv_label_set_text(objects.m15_17_night_label, itemName);
                lv_obj_set_style_text_color(objects.m15_17_night_label, lv_color_hex(labelColor), 0);
              }
            } else if(strcmp(nameValue, "12m-10m") == 0){
              if(strcmp(timeValue, "day") == 0){
                lv_label_set_text(objects.m10_12_day_label, itemName);
                lv_obj_set_style_text_color(objects.m10_12_day_label, lv_color_hex(labelColor), 0);
              } else {
                lv_label_set_text(objects.m10_12_night_label, itemName);
                lv_obj_set_style_text_color(objects.m10_12_night_label, lv_color_hex(labelColor), 0);
              }
            }
          } else {
            Serial.println("None found");
          }
          pBand = pBand->NextSiblingElement("band");
          itemCount++;
        }
      }

      calcVHFElement = childElement->FirstChildElement("calculatedvhfconditions");

      itemCount = 0;
      if (calcVHFElement) {
        XMLElement* pPhen = calcVHFElement->FirstChildElement("phenomenon");
        while (pPhen != nullptr) {
          const char* itemName = pPhen->GetText();
          if (itemName != nullptr) {
            const char* locValue = pPhen->Attribute("location");
            if(strcmp(locValue, "northern_hemi") == 0){
				      lv_label_set_text(objects.aurora_na_label, itemName);
            } else if(strcmp(locValue, "europe") == 0){
              lv_label_set_text(objects.skip_europe_label, itemName);
            } else if(strcmp(locValue, "north_america") == 0){
              lv_label_set_text(objects.skip_na_label, itemName);
            } else if(strcmp(locValue, "europe_6m") == 0){
              lv_label_set_text(objects.europe6m_label, itemName);
            } else if(strcmp(locValue, "europe_4m") == 0){
              lv_label_set_text(objects.europe4m_label, itemName);
            }
          } else {
            Serial.println("None found");
          }
          pPhen = pPhen->NextSiblingElement("phenomenon");
          itemCount++;
        }
      }
    }
  }
}


/*
 * Function to decode Weather condition to a font character for use in the Weather Tab
 */
const char *iconMap(const char *ow) {
    if (!strcmp(ow, "01d")) return "\uF00D"; // sun
    if (!strcmp(ow, "01n")) return "\uF02E"; // moon
    if (!strcmp(ow, "02d")) return "\uF002";
    if (!strcmp(ow, "09d")) return "\uF019";
    if (!strcmp(ow, "10d")) return "\uF008";
    if (!strcmp(ow, "11d")) return "\uF01E";
    if (!strcmp(ow, "13d")) return "\uF01B";
    if (!strcmp(ow, "50d")) return "\uF014";
    return "\uF07B"; // unknown
}

/*
 * Function to decode wind direction to a font character for use in the Weather Tab
 */
const char *dirIconMap(int dir) {
  if((dir >= 338) && (dir <=  22)) return("\uF05C");
  if((dir >=  23) && (dir <=  67)) return("\uF05A");
  if((dir >=  68) && (dir <= 112)) return("\uF059");
  if((dir >= 113) && (dir <= 157)) return("\uF05D");
  if((dir >= 158) && (dir <= 202)) return("\uF060");
  if((dir >= 203) && (dir <= 247)) return("\uF05E");
  if((dir >= 248) && (dir <= 292)) return("\uF061");
  if((dir >= 293) && (dir <= 337)) return("\uF05B");
}

/*
 * Function to update Weather tab display fields from parsing JSON fetched from fetchWeather function
 * Called every hour
 */
void updateWeatherScreen(){
  StaticJsonDocument<4096> doc;
  deserializeJson(doc, weatherBuffer);
  JsonObject cur;

  cur = doc["main"];

  float temp = round(cur["temp"].as<float>());
  float feels = round(cur["feels_like"].as<float>());
  float humidity = cur["humidity"];
  int temp_min = cur["temp_min"];
  int temp_max = cur["temp_max"];

  cur = doc["weather"][0];
  const char *cond = cur["main"];
  const char *desc = cur["description"];

  cur = doc["wind"];
  int wind_speed = round(cur["speed"].as<float>());
  int wind_deg = cur["deg"];
  float wind_gust = cur["gust"];

  lv_label_set_text_fmt(objects.now_temp_label, "%3.1f", temp);
  lv_label_set_text_fmt(objects.now_humi_label, "%3.1f", humidity);
  lv_label_set_text(objects.now_condition_label, cond);
  lv_label_set_text(objects.now_description_label, desc);
  lv_label_set_text_fmt(objects.now_feels_label, "%3.1f", feels);
  
  lv_label_set_text_fmt(objects.wind_speed_label, "%d", wind_speed);  
  lv_label_set_text_fmt(objects.wind_direction_label, "%03d°", wind_deg);
  lv_label_set_text(objects.wind_dir_label, dirIconMap(wind_deg));
  lv_label_set_text_fmt(objects.wind_gust_label, "%03.1f", wind_gust);

  lv_label_set_text_fmt(objects.today_low_label, "%03d°", temp_min);
  lv_label_set_text_fmt(objects.today_high_label, "%03d°", temp_max);
  cur = doc["clouds"];
  int cloud_cover = cur["all"];
  lv_label_set_text_fmt(objects.today_cloud_label, "%3d\%%", cloud_cover);
}

/*
 * Function that updates display fields/tabs based on time and/or preference changes.
 */
void updateScreen(){
  char dispS[32];

  updateTimeInfo();
  updateSeconds();

/*
 * every 24:
 * hours update clock if wifi enabled
 * 	update sunrise/sunset
 * 
 * every 1 hour:
 * 	update solar if wifi enabled
 * 	update weather if wifi enabled
 * 	update hour fields
 * 	update dates
 * 
 * every 10 minutes:
 * 	update sensors
 * 
 * every minute:
 * 	update minute fields
 * 
 * every second:
 * 	update seconds field
 */

  if((prevHour != zone1TM->tm_hour) || prefsNeedsUpdate){
    prevHour = zone1TM->tm_hour;
    updateDates();
    if((zone1TM->tm_hour % 3) == 0){
      if(lv_obj_has_state(objects.wifi_enable_checkbox, LV_STATE_CHECKED)){
        if(lv_obj_has_state(objects.wifi_solar_checkbox, LV_STATE_CHECKED)){
          fetchSolar();
        }
      }
    }
    if(zone1TM->tm_hour == 0){
      if(lv_obj_has_state(objects.wifi_enable_checkbox, LV_STATE_CHECKED) && 
         lv_obj_has_state(objects.wifi_time_checkbox, LV_STATE_CHECKED)){
        fetchTime();
      }
    }
  }
  if((prevMinute != zone1TM->tm_min) || prefsNeedsUpdate){
    prevMinute = zone1TM->tm_min;
    updateTimes();
    if(((zone1TM->tm_min % 10) == 0) || prefsNeedsUpdate){
      if(lv_obj_has_state(objects.wifi_enable_checkbox, LV_STATE_CHECKED)){
        if(lv_obj_has_state(objects.wifi_weather_checkbox, LV_STATE_CHECKED)){
          fetchWeather();
        }
      }
      updateSensors();
      updateSolarScreen();
      updateWeatherScreen();
    }
  }
  if(prefsNeedsUpdate){
    setBrightness(lv_slider_get_value(objects.brightness_slider));
    lv_label_set_text(objects.callsign_display_label, lv_textarea_get_text(objects.callsign_textarea));
    prefsPut();
  }
}
