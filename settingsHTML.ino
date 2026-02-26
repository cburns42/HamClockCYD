#include <WiFi.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "settingsHTML.h"
 
const char* settings_ap_ssid = "HamClock_AP";
const char* settings_ap_password = "HamClock";
 
AsyncWebServer server(80);
//WiFiServer server(80);
 
/*
 * This function is invoked with the user presses the WiFi Settings button on the Tools tab
 * It creates a WiFi Access Point, starts an webserver, displays a webpage that contains
 * an HTML form that is used to collect WiFi settings (SSID, Password) and Open Weather
 * settings (API Key, Latitude and Logitude)
 */
void settings_ap_setup(){
  WiFi.mode(WIFI_AP);
//  WiFi.begin(settings_ap_ssid, settings_ap_password);
  WiFi.softAP(settings_ap_ssid, settings_ap_password);
 
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: "); Serial.println(IP);

  server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request){
    boolean found_one = false;
    if (request->hasParam("ssid", true)) {
      String receivedValue = request->getParam("ssid", true)->value();
      receivedValue.toCharArray(ssid_value, receivedValue.length() + 1);
      Serial.print("Received ssid value: "); Serial.println(ssid_value);
      found_one = true;
    }
    if (request->hasParam("password", true)) {
      String receivedValue = request->getParam("password", true)->value();
      receivedValue.toCharArray(password_value, receivedValue.length() + 1);
      Serial.print("Received password value: "); Serial.println(password_value);
      found_one = true;
    }
    if (request->hasParam("openweatherkey", true)) {
      String receivedValue = request->getParam("openweatherkey", true)->value();
      receivedValue.toCharArray(openweather_key_value, receivedValue.length() + 1);
      Serial.print("Received openweatherkey value: "); Serial.println(openweather_key_value);
      found_one = true;
    }
    if (request->hasParam("openweatherlatitude", true)) {
      String receivedValue = request->getParam("openweatherlatitude", true)->value();
      openweather_latitude = receivedValue.toFloat();
      Serial.print("Received openweather latitude: "); Serial.println(receivedValue);
      found_one = true;
    }
    if (request->hasParam("openweatherlogitude", true)) {
      String receivedValue = request->getParam("openweatherlogitude", true)->value();
      openweather_longitude = receivedValue.toFloat();
      Serial.print("Received openweather logitude: "); Serial.println(receivedValue);
      found_one = true;
    }
    if(found_one){
      request->send(200, "text/html; charset=UTF-8", settingsDoneHTML);
      lv_obj_add_flag(objects.wifi_message_label, LV_OBJ_FLAG_HIDDEN);
      prefsNeedsUpdate = true;
    } else {
      request->send(400, "text/plain", "Error: No parameters found in POST request");
    }
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html; charset=UTF-8", settingsHTML);
  });
  server.begin();
}
