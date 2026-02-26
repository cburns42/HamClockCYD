#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_water_percent_24;
extern const lv_img_dsc_t img_altimeter_24;
extern const lv_img_dsc_t img_gauge_24;
extern const lv_img_dsc_t img_temperature_fahrenheit_24;
extern const lv_img_dsc_t img_temperature_celsius_24;
extern const lv_img_dsc_t img_wifi_on_24;
extern const lv_img_dsc_t img_clock_24;
extern const lv_img_dsc_t img_weather_24;
extern const lv_img_dsc_t img_wifi_alert_24;
extern const lv_img_dsc_t img_wifi_off_24;
extern const lv_img_dsc_t img_clock_alert_24;
extern const lv_img_dsc_t img_solar_24;
extern const lv_img_dsc_t img_solar_alert_24;
extern const lv_img_dsc_t img_weather_alert_24;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[14];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/