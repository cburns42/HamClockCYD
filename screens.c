#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC);
    {
        lv_obj_t *parent_obj = obj;
        {
            // displayTabs
            lv_obj_t *obj = lv_tabview_create(parent_obj);
            objects.display_tabs = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_tabview_set_tab_bar_position(obj, LV_DIR_TOP);
            lv_tabview_set_tab_bar_size(obj, 20);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // clockTab
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Clock");
                    objects.clock_tab = obj;
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // statusPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.status_panel = obj;
                            lv_obj_set_pos(obj, -13, 155);
                            lv_obj_set_size(obj, 50, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifiEnableImg
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.wifi_enable_img = obj;
                                    lv_obj_set_pos(obj, -13, -12);
                                    lv_obj_set_size(obj, 24, 24);
                                    lv_image_set_src(obj, &img_wifi_off_24);
                                }
                                {
                                    // timeEnableImg
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.time_enable_img = obj;
                                    lv_obj_set_pos(obj, 11, -12);
                                    lv_obj_set_size(obj, 24, 24);
                                    lv_image_set_src(obj, &img_clock_24);
                                }
                                {
                                    // solarEnableImg
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.solar_enable_img = obj;
                                    lv_obj_set_pos(obj, -13, 12);
                                    lv_obj_set_size(obj, 24, 24);
                                    lv_image_set_src(obj, &img_solar_24);
                                }
                                {
                                    // weatherEnableImg
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.weather_enable_img = obj;
                                    lv_obj_set_pos(obj, 11, 12);
                                    lv_obj_set_size(obj, 24, 24);
                                    lv_image_set_src(obj, &img_weather_24);
                                }
                            }
                        }
                        {
                            // sunDisplayPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.sun_display_panel = obj;
                            lv_obj_set_pos(obj, 37, 155);
                            lv_obj_set_size(obj, 110, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // sunriseTimeLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.sunrise_time_label = obj;
                                    lv_obj_set_pos(obj, 56, -9);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "07:15");
                                }
                                {
                                    // sunsetTextLabel_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.sunset_text_label_1 = obj;
                                    lv_obj_set_pos(obj, -11, -9);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Sunrise:");
                                }
                                {
                                    // sunsetTimeLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.sunset_time_label = obj;
                                    lv_obj_set_pos(obj, 57, 12);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "14:01");
                                }
                                {
                                    // sunsetTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.sunset_text_label = obj;
                                    lv_obj_set_pos(obj, -7, 12);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Sunset:");
                                }
                            }
                        }
                        {
                            // callsignDisplayPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.callsign_display_panel = obj;
                            lv_obj_set_pos(obj, 147, 155);
                            lv_obj_set_size(obj, 160, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // callsignDisplayLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.callsign_display_label = obj;
                                    lv_obj_set_pos(obj, -14, -14);
                                    lv_obj_set_size(obj, 160, 50);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // utcClockPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.utc_clock_panel = obj;
                            lv_obj_set_pos(obj, -13, -13);
                            lv_obj_set_size(obj, 160, 65);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // utcDateLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.utc_date_label = obj;
                                    lv_obj_set_pos(obj, -7, 35);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_label_set_text(obj, "Sunday Dec 28 2025");
                                }
                                {
                                    // utcTimeLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.utc_time_label = obj;
                                    lv_obj_set_pos(obj, -10, -14);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "23:59");
                                }
                                {
                                    // utcTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.utc_text_label = obj;
                                    lv_obj_set_pos(obj, 115, -10);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "UTC");
                                }
                            }
                        }
                        {
                            // zone1TimePanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.zone1_time_panel = obj;
                            lv_obj_set_pos(obj, 147, -13);
                            lv_obj_set_size(obj, 160, 65);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // zone1DateLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.zone1_date_label = obj;
                                    lv_obj_set_pos(obj, -7, 35);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_label_set_text(obj, "Sunday Dec 28 2025");
                                }
                                {
                                    // zone1TimeLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.zone1_time_label = obj;
                                    lv_obj_set_pos(obj, -10, -14);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "15:59");
                                }
                                {
                                    // zone1TextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.zone1_text_label = obj;
                                    lv_obj_set_pos(obj, 115, -10);
                                    lv_obj_set_size(obj, 28, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "EST");
                                }
                            }
                        }
                        {
                            // zone2TimePanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.zone2_time_panel = obj;
                            lv_obj_set_pos(obj, 147, 51);
                            lv_obj_set_size(obj, 160, 65);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // zone2DateLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.zone2_date_label = obj;
                                    lv_obj_set_pos(obj, -7, 35);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_label_set_text(obj, "Sunday Dec 28 2025");
                                }
                                {
                                    // zone2TimeLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.zone2_time_label = obj;
                                    lv_obj_set_pos(obj, -10, -14);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "13:59");
                                }
                                {
                                    // zone2TextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.zone2_text_label = obj;
                                    lv_obj_set_pos(obj, 115, -10);
                                    lv_obj_set_size(obj, 28, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "CST");
                                }
                            }
                        }
                        {
                            // secondsTimePanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.seconds_time_panel = obj;
                            lv_obj_set_pos(obj, -13, 51);
                            lv_obj_set_size(obj, 160, 65);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // secondsTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.seconds_text_label = obj;
                                    lv_obj_set_pos(obj, 35, 35);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_label_set_text(obj, "Seconds");
                                }
                                {
                                    // secondsTimeLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.seconds_time_label = obj;
                                    lv_obj_set_pos(obj, 32, -14);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, ":59");
                                }
                            }
                        }
                        {
                            // temperaturePanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.temperature_panel = obj;
                            lv_obj_set_pos(obj, -13, 115);
                            lv_obj_set_size(obj, 80, 40);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // temperatureImage
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.temperature_image = obj;
                                    lv_obj_set_pos(obj, 42, -10);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_image_set_src(obj, &img_temperature_fahrenheit_24);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                }
                                {
                                    // temperatureTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.temperature_text_label = obj;
                                    lv_obj_set_pos(obj, 1, 15);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Temperature");
                                }
                                {
                                    // temperatureLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.temperature_label = obj;
                                    lv_obj_set_pos(obj, -15, -10);
                                    lv_obj_set_size(obj, 55, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "101.2");
                                }
                            }
                        }
                        {
                            // humidityPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.humidity_panel = obj;
                            lv_obj_set_pos(obj, 67, 115);
                            lv_obj_set_size(obj, 80, 40);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // humidityImage
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.humidity_image = obj;
                                    lv_obj_set_pos(obj, 42, -10);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_image_set_src(obj, &img_water_percent_24);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                }
                                {
                                    // humidityTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.humidity_text_label = obj;
                                    lv_obj_set_pos(obj, 5, 15);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Humidity");
                                }
                                {
                                    // humidityLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.humidity_label = obj;
                                    lv_obj_set_pos(obj, -15, -10);
                                    lv_obj_set_size(obj, 55, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "98.9");
                                }
                            }
                        }
                        {
                            // barometerPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.barometer_panel = obj;
                            lv_obj_set_pos(obj, 147, 115);
                            lv_obj_set_size(obj, 80, 40);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // barometerImage
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.barometer_image = obj;
                                    lv_obj_set_pos(obj, 42, -10);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_image_set_src(obj, &img_gauge_24);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                }
                                {
                                    // barometerTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.barometer_text_label = obj;
                                    lv_obj_set_pos(obj, 5, 15);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Barometer");
                                }
                                {
                                    // barometerLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.barometer_label = obj;
                                    lv_obj_set_pos(obj, -15, -10);
                                    lv_obj_set_size(obj, 55, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "1001.2");
                                }
                            }
                        }
                        {
                            // altimeterPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.altimeter_panel = obj;
                            lv_obj_set_pos(obj, 227, 115);
                            lv_obj_set_size(obj, 80, 40);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // altimeterImage
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.altimeter_image = obj;
                                    lv_obj_set_pos(obj, 42, -10);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_image_set_src(obj, &img_altimeter_24);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                }
                                {
                                    // altimeterTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.altimeter_text_label = obj;
                                    lv_obj_set_pos(obj, 3, 15);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Altimeter");
                                }
                                {
                                    // altimeterLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.altimeter_label = obj;
                                    lv_obj_set_pos(obj, -15, -10);
                                    lv_obj_set_size(obj, 55, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "1001.2");
                                }
                            }
                        }
                    }
                }
                {
                    // weatherTab
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Weather");
                    objects.weather_tab = obj;
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // nowPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.now_panel = obj;
                            lv_obj_set_pos(obj, -4, -12);
                            lv_obj_set_size(obj, 300, 48);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // nowTempLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.now_temp_label = obj;
                                    lv_obj_set_pos(obj, -11, -11);
                                    lv_obj_set_size(obj, 80, 40);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, "110.9");
                                }
                                {
                                    // nowHumiLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.now_humi_label = obj;
                                    lv_obj_set_pos(obj, 174, -13);
                                    lv_obj_set_size(obj, 80, 40);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, "110.9");
                                }
                                {
                                    // nowTempTypeImg
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.now_temp_type_img = obj;
                                    lv_obj_set_pos(obj, 76, -14);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_image_set_src(obj, &img_temperature_fahrenheit_24);
                                }
                                {
                                    // nowHumiImg
                                    lv_obj_t *obj = lv_image_create(parent_obj);
                                    objects.now_humi_img = obj;
                                    lv_obj_set_pos(obj, 259, -11);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_image_set_src(obj, &img_water_percent_24);
                                }
                                {
                                    // nowFeelsLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.now_feels_label = obj;
                                    lv_obj_set_pos(obj, 108, 0);
                                    lv_obj_set_size(obj, 49, 20);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, "110.9");
                                }
                                {
                                    // nowFeelsTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.now_feels_txt_label = obj;
                                    lv_obj_set_pos(obj, 112, 20);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, "Feels Like");
                                }
                            }
                        }
                        {
                            // nowDescriptionPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.now_description_panel = obj;
                            lv_obj_set_pos(obj, -4, 35);
                            lv_obj_set_size(obj, 300, 48);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // weatherIconLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.weather_icon_label = obj;
                                    lv_obj_set_pos(obj, 13, -5);
                                    lv_obj_set_size(obj, 32, 32);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &ui_font_weather_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uF00D");
                                }
                                {
                                    // nowConditionLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.now_condition_label = obj;
                                    lv_obj_set_pos(obj, 62, -13);
                                    lv_obj_set_size(obj, 200, 24);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, "Clear");
                                }
                                {
                                    // nowDescriptionLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.now_description_label = obj;
                                    lv_obj_set_pos(obj, 62, 9);
                                    lv_obj_set_size(obj, 200, 24);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, "Clear");
                                }
                            }
                        }
                        {
                            // windPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wind_panel = obj;
                            lv_obj_set_pos(obj, -4, 82);
                            lv_obj_set_size(obj, 300, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // windSpeedLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.wind_speed_label = obj;
                                    lv_obj_set_pos(obj, 63, -6);
                                    lv_obj_set_size(obj, 60, 40);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, "199");
                                }
                                {
                                    // windSpeedtxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.wind_speedtxt_label = obj;
                                    lv_obj_set_pos(obj, 123, -7);
                                    lv_obj_set_size(obj, 50, 20);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, " mph");
                                }
                                {
                                    // windDirLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.wind_dir_label = obj;
                                    lv_obj_set_pos(obj, -9, -13);
                                    lv_obj_set_size(obj, 32, 32);
                                    lv_obj_set_style_text_font(obj, &ui_font_weather_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, " \uF05a");
                                }
                                {
                                    // windDirectionLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.wind_direction_label = obj;
                                    lv_obj_set_pos(obj, -9, 21);
                                    lv_obj_set_size(obj, 40, 20);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "199\u00B0");
                                }
                                {
                                    // windGustTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.wind_gust_txt_label = obj;
                                    lv_obj_set_pos(obj, 128, 17);
                                    lv_obj_set_size(obj, 50, 20);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Gust:");
                                }
                                {
                                    // windGustLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.wind_gust_label = obj;
                                    lv_obj_set_pos(obj, 179, 17);
                                    lv_obj_set_size(obj, 50, 20);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "199.1");
                                }
                            }
                        }
                        {
                            // todayPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.today_panel = obj;
                            lv_obj_set_pos(obj, -4, 137);
                            lv_obj_set_size(obj, 300, 40);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // todayHighTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.today_high_txt_label = obj;
                                    lv_obj_set_pos(obj, -14, -10);
                                    lv_obj_set_size(obj, 32, 32);
                                    lv_obj_set_style_text_font(obj, &ui_font_weather_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_weather_36, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, " \uF058");
                                }
                                {
                                    // todayHighLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.today_high_label = obj;
                                    lv_obj_set_pos(obj, 23, -4);
                                    lv_obj_set_size(obj, 40, 20);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "199\u00B0");
                                }
                                {
                                    // todayLowTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.today_low_txt_label = obj;
                                    lv_obj_set_pos(obj, 85, -10);
                                    lv_obj_set_size(obj, 32, 32);
                                    lv_obj_set_style_text_font(obj, &ui_font_weather_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_weather_36, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, " \uF044");
                                }
                                {
                                    // todayLowLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.today_low_label = obj;
                                    lv_obj_set_pos(obj, 117, -4);
                                    lv_obj_set_size(obj, 40, 20);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "199\u00B0");
                                }
                                {
                                    // todayCloudTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.today_cloud_txt_label = obj;
                                    lv_obj_set_pos(obj, 179, -11);
                                    lv_obj_set_size(obj, 36, 36);
                                    lv_obj_set_style_text_font(obj, &ui_font_weather_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_weather_24, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, " \uF041");
                                }
                                {
                                    // todayCloudLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.today_cloud_label = obj;
                                    lv_obj_set_pos(obj, 219, -4);
                                    lv_obj_set_size(obj, 55, 20);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, "100%");
                                }
                            }
                        }
                    }
                }
                {
                    // solarTab
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Solar");
                    objects.solar_tab = obj;
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // vhfConditionsPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.vhf_conditions_panel = obj;
                            lv_obj_set_pos(obj, 147, 87);
                            lv_obj_set_size(obj, 153, 75);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // vhfTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.vhf_text_label = obj;
                                    lv_obj_set_pos(obj, -14, -14);
                                    lv_obj_set_size(obj, 152, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "VHF Conditions");
                                }
                                {
                                    // auroraNATxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.aurora_na_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 2);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Aurora NA");
                                }
                                {
                                    // auroraNALabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.aurora_na_label = obj;
                                    lv_obj_set_pos(obj, 50, 2);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Closed");
                                }
                                {
                                    // skipEuropeLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.skip_europe_label = obj;
                                    lv_obj_set_pos(obj, 50, 13);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Closed");
                                }
                                {
                                    // skipEuropeTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.skip_europe_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 13);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "E-Skip Europe");
                                }
                                {
                                    // skipNALabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.skip_na_label = obj;
                                    lv_obj_set_pos(obj, 50, 24);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Closed");
                                }
                                {
                                    // skipNATxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.skip_na_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 24);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "E-Skip Europe");
                                }
                                {
                                    // europe6mLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.europe6m_label = obj;
                                    lv_obj_set_pos(obj, 50, 35);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Closed");
                                }
                                {
                                    // europe6mTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.europe6m_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 35);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Europe 6m");
                                }
                                {
                                    // europe4mLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.europe4m_label = obj;
                                    lv_obj_set_pos(obj, 50, 46);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Closed");
                                }
                                {
                                    // europe4mTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.europe4m_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 46);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Europe 4m");
                                }
                            }
                        }
                        {
                            // solarConditionsPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.solar_conditions_panel = obj;
                            lv_obj_set_pos(obj, -10, 0);
                            lv_obj_set_size(obj, 153, 162);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // solarTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.solar_text_label = obj;
                                    lv_obj_set_pos(obj, -14, -14);
                                    lv_obj_set_size(obj, 152, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Solar Conditions");
                                }
                                {
                                    // solarFluxLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.solar_flux_label = obj;
                                    lv_obj_set_pos(obj, 50, 2);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "118");
                                }
                                {
                                    // solarFluxTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.solar_flux_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 2);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Solar Flux");
                                }
                                {
                                    // aindexLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.aindex_label = obj;
                                    lv_obj_set_pos(obj, 50, 13);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "6");
                                }
                                {
                                    // aindexTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.aindex_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 13);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "A Index");
                                }
                                {
                                    // kindexLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.kindex_label = obj;
                                    lv_obj_set_pos(obj, 50, 24);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "6");
                                }
                                {
                                    // kindexTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.kindex_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 24);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "K Index");
                                }
                                {
                                    // kindexNTLabel_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.kindex_nt_label_1 = obj;
                                    lv_obj_set_pos(obj, 50, 35);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "2");
                                }
                                {
                                    // kindexNTTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.kindex_nt_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 35);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "K Index Night");
                                }
                                {
                                    // xrayLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.xray_label = obj;
                                    lv_obj_set_pos(obj, 50, 46);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "B8.0");
                                }
                                {
                                    // xrayTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.xray_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 46);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Xray");
                                }
                                {
                                    // sunspotsLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.sunspots_label = obj;
                                    lv_obj_set_pos(obj, 50, 57);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "33");
                                }
                                {
                                    // sunspotsTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.sunspots_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 57);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Sunspots");
                                }
                                {
                                    // heliumLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.helium_label = obj;
                                    lv_obj_set_pos(obj, 50, 68);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "128.2");
                                }
                                {
                                    // heliumTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.helium_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 68);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Helium Line");
                                }
                                {
                                    // ProtonFluxLabelLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.proton_flux_label_label = obj;
                                    lv_obj_set_pos(obj, 50, 79);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "12");
                                }
                                {
                                    // ProtonFluxTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.proton_flux_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 79);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Proton Flux");
                                }
                                {
                                    // ElectonFluxLabelLabel_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.electon_flux_label_label_1 = obj;
                                    lv_obj_set_pos(obj, 50, 90);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "2170");
                                }
                                {
                                    // ElectonFluxTxtLabel_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.electon_flux_txt_label_1 = obj;
                                    lv_obj_set_pos(obj, -12, 90);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Electon Flux");
                                }
                                {
                                    // auroraLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.aurora_label = obj;
                                    lv_obj_set_pos(obj, 50, 101);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "3");
                                }
                                {
                                    // auroraTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.aurora_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 101);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Aurora");
                                }
                                {
                                    // normalizationLabel_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.normalization_label_1 = obj;
                                    lv_obj_set_pos(obj, 50, 112);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "1.99");
                                }
                                {
                                    // normalizationTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.normalization_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 112);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Normalization");
                                }
                                {
                                    // solarwindLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.solarwind_label = obj;
                                    lv_obj_set_pos(obj, 50, 123);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "477.1");
                                }
                                {
                                    // solarwindTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.solarwind_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 123);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Solar Wind");
                                }
                                {
                                    // magneticfieldLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.magneticfield_label = obj;
                                    lv_obj_set_pos(obj, 50, 134);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "-1.9");
                                }
                                {
                                    // magneticfieldTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.magneticfield_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 134);
                                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Magnetic Field");
                                }
                            }
                        }
                        {
                            // calculatedConditionsPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.calculated_conditions_panel = obj;
                            lv_obj_set_pos(obj, 147, 0);
                            lv_obj_set_size(obj, 152, 76);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // calcTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.calc_text_label = obj;
                                    lv_obj_set_pos(obj, -14, -14);
                                    lv_obj_set_size(obj, 152, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Calculated Conditions");
                                }
                                {
                                    // calcBandLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.calc_band_label = obj;
                                    lv_obj_set_pos(obj, -14, 2);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Band");
                                }
                                {
                                    // calcDayLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.calc_day_label = obj;
                                    lv_obj_set_pos(obj, 1, 2);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Day");
                                }
                                {
                                    // calcNightLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.calc_night_label = obj;
                                    lv_obj_set_pos(obj, 14, 2);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Night");
                                }
                                {
                                    // m40-80BandLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m40_80_band_label = obj;
                                    lv_obj_set_pos(obj, -12, 15);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "80m-40m");
                                }
                                {
                                    // m40-80DayLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m40_80_day_label = obj;
                                    lv_obj_set_pos(obj, 0, 15);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Good");
                                }
                                {
                                    // m40-80NightLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m40_80_night_label = obj;
                                    lv_obj_set_pos(obj, 12, 15);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Good");
                                }
                                {
                                    // m20-30BandLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m20_30_band_label = obj;
                                    lv_obj_set_pos(obj, -12, 26);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "20m-30m");
                                }
                                {
                                    // m20-30DayLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m20_30_day_label = obj;
                                    lv_obj_set_pos(obj, 0, 26);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Good");
                                }
                                {
                                    // m20-30NightLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m20_30_night_label = obj;
                                    lv_obj_set_pos(obj, 12, 26);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Good");
                                }
                                {
                                    // m15-17NightLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m15_17_night_label = obj;
                                    lv_obj_set_pos(obj, 12, 37);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Good");
                                }
                                {
                                    // m15-15BandLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m15_15_band_label = obj;
                                    lv_obj_set_pos(obj, -12, 37);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "15m-17m");
                                }
                                {
                                    // m15-17DayLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m15_17_day_label = obj;
                                    lv_obj_set_pos(obj, 0, 37);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Good");
                                }
                                {
                                    // m10-12BandLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m10_12_band_label = obj;
                                    lv_obj_set_pos(obj, -12, 48);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "12m-12m");
                                }
                                {
                                    // m10-12DayLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m10_12_day_label = obj;
                                    lv_obj_set_pos(obj, 0, 48);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Good");
                                }
                                {
                                    // m10-12NightLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.m10_12_night_label = obj;
                                    lv_obj_set_pos(obj, 12, 48);
                                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Good");
                                }
                            }
                        }
                        {
                            // lastUpdatePanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.last_update_panel = obj;
                            lv_obj_set_pos(obj, -8, 167);
                            lv_obj_set_size(obj, 308, 30);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // lastUpdateTextLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.last_update_text_label = obj;
                                    lv_obj_set_pos(obj, -14, -14);
                                    lv_obj_set_size(obj, 152, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                    lv_label_set_text(obj, "Last Updated:");
                                }
                                {
                                    // lastUpdatedTxtLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.last_updated_txt_label = obj;
                                    lv_obj_set_pos(obj, -12, 2);
                                    lv_obj_set_size(obj, 303, LV_SIZE_CONTENT);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Last Updated Date/Time");
                                }
                            }
                        }
                    }
                }
                {
                    // toolsTab
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Tools");
                    objects.tools_tab = obj;
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // manualSetButton
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.manual_set_button = obj;
                            lv_obj_set_pos(obj, 188, 106);
                            lv_obj_set_size(obj, 110, 25);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // manualSetLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.manual_set_label = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Manual Set Time");
                                }
                            }
                        }
                        {
                            // callsignLabel
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.callsign_label = obj;
                            lv_obj_set_pos(obj, 153, -6);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Callsign:");
                        }
                        {
                            // callsignTextarea
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            objects.callsign_textarea = obj;
                            lv_obj_set_pos(obj, 219, -9);
                            lv_obj_set_size(obj, 80, 23);
                            lv_textarea_set_max_length(obj, 32);
                            lv_textarea_set_placeholder_text(obj, "Callsign");
                            lv_textarea_set_one_line(obj, true);
                            lv_textarea_set_password_mode(obj, false);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // wifiTimeCheckbox
                            lv_obj_t *obj = lv_checkbox_create(parent_obj);
                            objects.wifi_time_checkbox = obj;
                            lv_obj_set_pos(obj, -6, 23);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_checkbox_set_text(obj, "WiFi Time Sync");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // wifiSolarCheckbox
                            lv_obj_t *obj = lv_checkbox_create(parent_obj);
                            objects.wifi_solar_checkbox = obj;
                            lv_obj_set_pos(obj, 153, 22);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_checkbox_set_text(obj, "WiFi Solar");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // wifiWeatherCheckbox
                            lv_obj_t *obj = lv_checkbox_create(parent_obj);
                            objects.wifi_weather_checkbox = obj;
                            lv_obj_set_pos(obj, -6, 48);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_checkbox_set_text(obj, "WiFi Weather");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // wifiEnableCheckbox
                            lv_obj_t *obj = lv_checkbox_create(parent_obj);
                            objects.wifi_enable_checkbox = obj;
                            lv_obj_set_pos(obj, 153, 47);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_checkbox_set_text(obj, "WiFi Enable");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // tempSettingLabel
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.temp_setting_label = obj;
                            lv_obj_set_pos(obj, -6, 108);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Temp:");
                        }
                        {
                            // zone1Label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.zone1_label = obj;
                            lv_obj_set_pos(obj, -6, 77);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Zone 1:");
                        }
                        {
                            // zone2Dropdown
                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                            objects.zone2_dropdown = obj;
                            lv_obj_set_pos(obj, 219, 74);
                            lv_obj_set_size(obj, 80, LV_SIZE_CONTENT);
                            lv_dropdown_set_options(obj, "-12\n-11\n-10\n-9\n-8\n-7\n-6\n-5\n-4\n-3\n-2\n-1\n0\n+1\n+2\n+3\n+4\n+5\n+6\n+7\n+8\n+9\n+10\n+11\n+12");
                            lv_dropdown_set_selected(obj, 6);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // zone2Label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.zone2_label = obj;
                            lv_obj_set_pos(obj, 161, 77);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Zone 2:");
                        }
                        {
                            // zone1Dropdown
                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                            objects.zone1_dropdown = obj;
                            lv_obj_set_pos(obj, 52, 73);
                            lv_obj_set_size(obj, 80, LV_SIZE_CONTENT);
                            lv_dropdown_set_options(obj, "-12\n-11\n-10\n-9\n-8\n-7\n-6\n-5\n-4\n-3\n-2\n-1\n0\n+1\n+2\n+3\n+4\n+5\n+6\n+7\n+8\n+9\n+10\n+11\n+12");
                            lv_dropdown_set_selected(obj, 7);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // temperatureDropdown
                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                            objects.temperature_dropdown = obj;
                            lv_obj_set_pos(obj, 42, 105);
                            lv_obj_set_size(obj, 90, LV_SIZE_CONTENT);
                            lv_dropdown_set_options(obj, "imperial\nmetric");
                            lv_dropdown_set_selected(obj, 0);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // wifiSetButton
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.wifi_set_button = obj;
                            lv_obj_set_pos(obj, 188, 136);
                            lv_obj_set_size(obj, 110, 25);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifiSetLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.wifi_set_label = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "WiFi Settings");
                                }
                            }
                        }
                        {
                            // settingsResetButton
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.settings_reset_button = obj;
                            lv_obj_set_pos(obj, -6, 136);
                            lv_obj_set_size(obj, 110, 25);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settingsResetLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_reset_label = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Clear Settings");
                                }
                            }
                        }
                        {
                            // brightnessSlider
                            lv_obj_t *obj = lv_slider_create(parent_obj);
                            objects.brightness_slider = obj;
                            lv_obj_set_pos(obj, -6, -3);
                            lv_obj_set_size(obj, 100, 5);
                            lv_slider_set_value(obj, 25, LV_ANIM_OFF);
                        }
                        {
                            // brightnessLabel
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.brightness_label = obj;
                            lv_obj_set_pos(obj, 31, 5);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_8, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Brightness");
                        }
                        {
                            // wifiMessageLabel
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_message_label = obj;
                            lv_obj_set_pos(obj, -3, 167);
                            lv_obj_set_size(obj, 300, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff802121), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                            lv_label_set_text(obj, "Enter settings by connecting to SSID HamClock_AP, Password HamClock");
                        }
                        {
                            // toolsEntryPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.tools_entry_panel = obj;
                            lv_obj_set_pos(obj, -13, 65);
                            lv_obj_set_size(obj, 320, 140);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // toolsKeyboard
                                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                                    objects.tools_keyboard = obj;
                                    lv_obj_set_pos(obj, -14, -14);
                                    lv_obj_set_size(obj, 320, 140);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // settingsPanel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.settings_panel = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 300, 170);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // saveSettingsButton
                                    lv_obj_t *obj = lv_button_create(parent_obj);
                                    objects.save_settings_button = obj;
                                    lv_obj_set_pos(obj, 3, 111);
                                    lv_obj_set_size(obj, 50, 20);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // saveSettingsLabel
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.save_settings_label = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "Save");
                                        }
                                    }
                                }
                                {
                                    // cancelSettingsButton
                                    lv_obj_t *obj = lv_button_create(parent_obj);
                                    objects.cancel_settings_button = obj;
                                    lv_obj_set_pos(obj, 60, 111);
                                    lv_obj_set_size(obj, 50, 20);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // cancelSettingsLabel
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.cancel_settings_label = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "Cancel");
                                        }
                                    }
                                }
                                {
                                    // dateSettingCalendar
                                    lv_obj_t *obj = lv_calendar_create(parent_obj);
                                    objects.date_setting_calendar = obj;
                                    lv_obj_set_pos(obj, 128, -8);
                                    lv_obj_set_size(obj, 150, 150);
                                    lv_calendar_header_arrow_create(obj);
                                    lv_calendar_set_today_date(obj, 2022, 11, 1);
                                    lv_calendar_set_showed_date(obj, 2022, 11);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // setHoursLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.set_hours_label = obj;
                                    lv_obj_set_pos(obj, -9, -2);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Hours:");
                                }
                                {
                                    // tensHoursDropdown
                                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                    objects.tens_hours_dropdown = obj;
                                    lv_obj_set_pos(obj, 65, -3);
                                    lv_obj_set_size(obj, 30, LV_SIZE_CONTENT);
                                    lv_dropdown_set_options(obj, "0\n1\n2");
                                    lv_dropdown_set_selected(obj, 0);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                }
                                {
                                    // hoursDropdown
                                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                    objects.hours_dropdown = obj;
                                    lv_obj_set_pos(obj, 95, -3);
                                    lv_obj_set_size(obj, 30, LV_SIZE_CONTENT);
                                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9");
                                    lv_dropdown_set_selected(obj, 3);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                }
                                {
                                    // tensMinDropdown
                                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                    objects.tens_min_dropdown = obj;
                                    lv_obj_set_pos(obj, 65, 29);
                                    lv_obj_set_size(obj, 30, LV_SIZE_CONTENT);
                                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5");
                                    lv_dropdown_set_selected(obj, 0);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                }
                                {
                                    // MinDropdown
                                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                    objects.min_dropdown = obj;
                                    lv_obj_set_pos(obj, 95, 29);
                                    lv_obj_set_size(obj, 30, LV_SIZE_CONTENT);
                                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9");
                                    lv_dropdown_set_selected(obj, 3);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                }
                                {
                                    // minutesSettingLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.minutes_setting_label = obj;
                                    lv_obj_set_pos(obj, -9, 32);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Minutes:");
                                }
                                {
                                    // secondsSettingLabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.seconds_setting_label = obj;
                                    lv_obj_set_pos(obj, -9, 65);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Seconds:");
                                }
                                {
                                    // tensSecDropdown
                                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                    objects.tens_sec_dropdown = obj;
                                    lv_obj_set_pos(obj, 65, 61);
                                    lv_obj_set_size(obj, 30, LV_SIZE_CONTENT);
                                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5");
                                    lv_dropdown_set_selected(obj, 0);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                }
                                {
                                    // secDropdown
                                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                    objects.sec_dropdown = obj;
                                    lv_obj_set_pos(obj, 95, 61);
                                    lv_obj_set_size(obj, 30, LV_SIZE_CONTENT);
                                    lv_dropdown_set_options(obj, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9");
                                    lv_dropdown_set_selected(obj, 3);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
