#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *display_tabs;
    lv_obj_t *clock_tab;
    lv_obj_t *status_panel;
    lv_obj_t *wifi_enable_img;
    lv_obj_t *time_enable_img;
    lv_obj_t *solar_enable_img;
    lv_obj_t *weather_enable_img;
    lv_obj_t *sun_display_panel;
    lv_obj_t *sunrise_time_label;
    lv_obj_t *sunset_text_label_1;
    lv_obj_t *sunset_time_label;
    lv_obj_t *sunset_text_label;
    lv_obj_t *callsign_display_panel;
    lv_obj_t *callsign_display_label;
    lv_obj_t *utc_clock_panel;
    lv_obj_t *utc_date_label;
    lv_obj_t *utc_time_label;
    lv_obj_t *utc_text_label;
    lv_obj_t *zone1_time_panel;
    lv_obj_t *zone1_date_label;
    lv_obj_t *zone1_time_label;
    lv_obj_t *zone1_text_label;
    lv_obj_t *zone2_time_panel;
    lv_obj_t *zone2_date_label;
    lv_obj_t *zone2_time_label;
    lv_obj_t *zone2_text_label;
    lv_obj_t *seconds_time_panel;
    lv_obj_t *seconds_text_label;
    lv_obj_t *seconds_time_label;
    lv_obj_t *temperature_panel;
    lv_obj_t *temperature_image;
    lv_obj_t *temperature_text_label;
    lv_obj_t *temperature_label;
    lv_obj_t *humidity_panel;
    lv_obj_t *humidity_image;
    lv_obj_t *humidity_text_label;
    lv_obj_t *humidity_label;
    lv_obj_t *barometer_panel;
    lv_obj_t *barometer_image;
    lv_obj_t *barometer_text_label;
    lv_obj_t *barometer_label;
    lv_obj_t *altimeter_panel;
    lv_obj_t *altimeter_image;
    lv_obj_t *altimeter_text_label;
    lv_obj_t *altimeter_label;
    lv_obj_t *weather_tab;
    lv_obj_t *now_panel;
    lv_obj_t *now_temp_label;
    lv_obj_t *now_humi_label;
    lv_obj_t *now_temp_type_img;
    lv_obj_t *now_humi_img;
    lv_obj_t *now_feels_label;
    lv_obj_t *now_feels_txt_label;
    lv_obj_t *now_description_panel;
    lv_obj_t *weather_icon_label;
    lv_obj_t *now_condition_label;
    lv_obj_t *now_description_label;
    lv_obj_t *wind_panel;
    lv_obj_t *wind_speed_label;
    lv_obj_t *wind_speedtxt_label;
    lv_obj_t *wind_dir_label;
    lv_obj_t *wind_direction_label;
    lv_obj_t *wind_gust_txt_label;
    lv_obj_t *wind_gust_label;
    lv_obj_t *today_panel;
    lv_obj_t *today_high_txt_label;
    lv_obj_t *today_high_label;
    lv_obj_t *today_low_txt_label;
    lv_obj_t *today_low_label;
    lv_obj_t *today_cloud_txt_label;
    lv_obj_t *today_cloud_label;
    lv_obj_t *solar_tab;
    lv_obj_t *vhf_conditions_panel;
    lv_obj_t *vhf_text_label;
    lv_obj_t *aurora_na_txt_label;
    lv_obj_t *aurora_na_label;
    lv_obj_t *skip_europe_label;
    lv_obj_t *skip_europe_txt_label;
    lv_obj_t *skip_na_label;
    lv_obj_t *skip_na_txt_label;
    lv_obj_t *europe6m_label;
    lv_obj_t *europe6m_txt_label;
    lv_obj_t *europe4m_label;
    lv_obj_t *europe4m_txt_label;
    lv_obj_t *solar_conditions_panel;
    lv_obj_t *solar_text_label;
    lv_obj_t *solar_flux_label;
    lv_obj_t *solar_flux_txt_label;
    lv_obj_t *aindex_label;
    lv_obj_t *aindex_txt_label;
    lv_obj_t *kindex_label;
    lv_obj_t *kindex_txt_label;
    lv_obj_t *kindex_nt_label_1;
    lv_obj_t *kindex_nt_txt_label;
    lv_obj_t *xray_label;
    lv_obj_t *xray_txt_label;
    lv_obj_t *sunspots_label;
    lv_obj_t *sunspots_txt_label;
    lv_obj_t *helium_label;
    lv_obj_t *helium_txt_label;
    lv_obj_t *proton_flux_label_label;
    lv_obj_t *proton_flux_txt_label;
    lv_obj_t *electon_flux_label_label_1;
    lv_obj_t *electon_flux_txt_label_1;
    lv_obj_t *aurora_label;
    lv_obj_t *aurora_txt_label;
    lv_obj_t *normalization_label_1;
    lv_obj_t *normalization_txt_label;
    lv_obj_t *solarwind_label;
    lv_obj_t *solarwind_txt_label;
    lv_obj_t *magneticfield_label;
    lv_obj_t *magneticfield_txt_label;
    lv_obj_t *calculated_conditions_panel;
    lv_obj_t *calc_text_label;
    lv_obj_t *calc_band_label;
    lv_obj_t *calc_day_label;
    lv_obj_t *calc_night_label;
    lv_obj_t *m40_80_band_label;
    lv_obj_t *m40_80_day_label;
    lv_obj_t *m40_80_night_label;
    lv_obj_t *m20_30_band_label;
    lv_obj_t *m20_30_day_label;
    lv_obj_t *m20_30_night_label;
    lv_obj_t *m15_17_night_label;
    lv_obj_t *m15_15_band_label;
    lv_obj_t *m15_17_day_label;
    lv_obj_t *m10_12_band_label;
    lv_obj_t *m10_12_day_label;
    lv_obj_t *m10_12_night_label;
    lv_obj_t *last_update_panel;
    lv_obj_t *last_update_text_label;
    lv_obj_t *last_updated_txt_label;
    lv_obj_t *tools_tab;
    lv_obj_t *manual_set_button;
    lv_obj_t *manual_set_label;
    lv_obj_t *callsign_label;
    lv_obj_t *callsign_textarea;
    lv_obj_t *wifi_time_checkbox;
    lv_obj_t *wifi_solar_checkbox;
    lv_obj_t *wifi_weather_checkbox;
    lv_obj_t *wifi_enable_checkbox;
    lv_obj_t *temp_setting_label;
    lv_obj_t *zone1_label;
    lv_obj_t *zone2_dropdown;
    lv_obj_t *zone2_label;
    lv_obj_t *zone1_dropdown;
    lv_obj_t *temperature_dropdown;
    lv_obj_t *wifi_set_button;
    lv_obj_t *wifi_set_label;
    lv_obj_t *settings_reset_button;
    lv_obj_t *settings_reset_label;
    lv_obj_t *brightness_slider;
    lv_obj_t *brightness_label;
    lv_obj_t *wifi_message_label;
    lv_obj_t *tools_entry_panel;
    lv_obj_t *tools_keyboard;
    lv_obj_t *settings_panel;
    lv_obj_t *save_settings_button;
    lv_obj_t *save_settings_label;
    lv_obj_t *cancel_settings_button;
    lv_obj_t *cancel_settings_label;
    lv_obj_t *date_setting_calendar;
    lv_obj_t *set_hours_label;
    lv_obj_t *tens_hours_dropdown;
    lv_obj_t *hours_dropdown;
    lv_obj_t *tens_min_dropdown;
    lv_obj_t *min_dropdown;
    lv_obj_t *minutes_setting_label;
    lv_obj_t *seconds_setting_label;
    lv_obj_t *tens_sec_dropdown;
    lv_obj_t *sec_dropdown;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/