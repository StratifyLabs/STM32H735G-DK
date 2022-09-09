#ifndef DESIGNLAB_THEMES_THEMES_H_
#define DESIGNLAB_THEMES_THEMES_H_


#include <lvgl_api.h>

#if defined __cplusplus
extern "C" {
#endif

const lvgl_api_theme_descriptor_t *themes_get_theme(int offset);
void themes_initialize();

#if defined __cplusplus
}
#endif

#endif // DESIGNLAB_THEMES_THEMES_H_

