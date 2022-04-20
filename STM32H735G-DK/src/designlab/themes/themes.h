//
// Created by Tyler Gilbert on 1/24/22.
//

#ifndef STM32H735G_DK_THEMES_H
#define STM32H735G_DK_THEMES_H

#include <lvgl_api.h>

extern lv_theme_t default_dark_small_theme;
extern lv_theme_t default_light_small_theme;

lv_theme_t * default_light_small_theme_initialize(lv_disp_t * disp, lv_theme_t * parent);
lv_theme_t * default_dark_small_theme_initialize(lv_disp_t * disp, lv_theme_t * parent);

#endif //STM32H735G_DK_THEMES_H
