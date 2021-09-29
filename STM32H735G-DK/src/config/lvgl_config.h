#ifndef LVGL_CONFIG_H
#define LVGL_CONFIG_H

#if _IS_BOOT == 0
void lvgl_config_initialize_display();
void lvgl_config_start();
int lvgl_get_font(void *args);
#endif

#endif // LVGL_CONFIG_H
