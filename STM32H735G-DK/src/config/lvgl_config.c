
#include <lvgl.h>
#include <lvgl_api.h>
#include <sos/config.h>

#include "config.h"
#include "os_config.h"

#include "stm32/stm32h735g_discovery_conf.h"
#include "stm32/stm32h735g_discovery_lcd.h"
#include "stm32/stm32h735g_discovery_ts.h"

#if _IS_BOOT == 0

#include "designlab/fonts/fonts.h"
#include "designlab/themes/themes.h"

#define SCREEN_MEM_SIZE (LCD_DEFAULT_WIDTH * LCD_DEFAULT_HEIGHT * 4)

static void *reload_address = NULL;
static lv_disp_drv_t *reload_disp_drv = NULL;
extern LTDC_HandleTypeDef hlcd_ltdc;

void mcu_core_ltdc_isr(){
  HAL_LTDC_IRQHandler(&hlcd_ltdc);
}

/*Static or global buffer(s). The second buffer is optional*/
static void svcall_init_hardware(void *args) {
  CORTEXM_SVCALL_ENTER();
  MCU_UNUSED_ARGUMENT(args);

  BSP_LCD_InitEx(CONFIG_LCD_INSTANCE, LCD_ORIENTATION_LANDSCAPE,
                 LCD_PIXEL_FORMAT_ARGB8888, LCD_DEFAULT_WIDTH,
                 LCD_DEFAULT_HEIGHT);

  TS_Init_t hTS = {};
  hTS.Orientation = TS_SWAP_XY;
  hTS.Accuracy = 0;
  hTS.Width = LCD_DEFAULT_WIDTH;
  hTS.Height = LCD_DEFAULT_HEIGHT;
  BSP_TS_Init(0, &hTS);

  //HAL_LTDC_ProgramLineEvent(&hlcd_ltdc, 272);
  //cortexm_enable_irq(LTDC_IRQn);
}

static void root_set_video_memory(void *address) {

  sos_config.cache.clean_data_block(address, SCREEN_MEM_SIZE);

  BSP_LCD_LayerConfig_t config = {};
  config.X1 = LCD_DEFAULT_WIDTH;
  config.Y1 = LCD_DEFAULT_HEIGHT;
  config.PixelFormat = LCD_PIXEL_FORMAT_ARGB8888;
  config.Address = (u32)address;
  BSP_LCD_ConfigLayer(0, 0, &config);
}



static void svcall_flush(void *args) {
  CORTEXM_SVCALL_ENTER();
  // just need to point the LCD to the new memory pointer
  root_set_video_memory(args);
}

static void flush_callback(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                           lv_color_t *color_p) {
  MCU_UNUSED_ARGUMENT(area);
  reload_disp_drv = disp_drv;
  cortexm_svcall(svcall_flush, color_p);

  /* IMPORTANT!!!
   * Inform the graphics library that you are ready with the flushing*/
  lv_disp_flush_ready(disp_drv);
}

static void gpu_fill_callback(lv_disp_drv_t *disp_drv, lv_color_t *dest_buf,
                              const lv_area_t *dest_area,
                              const lv_area_t *fill_area, lv_color_t color) {
  MCU_UNUSED_ARGUMENT(disp_drv);
  MCU_UNUSED_ARGUMENT(dest_buf);
  MCU_UNUSED_ARGUMENT(dest_area);
  MCU_UNUSED_ARGUMENT(fill_area);
  MCU_UNUSED_ARGUMENT(color);
}

static void clean_cache_callback(lv_disp_drv_t *disp_drv, u32 address) {
  /* Example for Cortex-M (CMSIS) */
  MCU_UNUSED_ARGUMENT(disp_drv);
  MCU_UNUSED_ARGUMENT(address);
}

static void svcall_touch_read(void *args) { BSP_TS_GetState(0, args); }

static void touch_read_callback(lv_indev_drv_t *drv, lv_indev_data_t *data) {
  MCU_UNUSED_ARGUMENT(drv);
  TS_State_t state;
  cortexm_svcall(svcall_touch_read, &state);

  if (state.TouchDetected) {
    data->point.x = state.TouchX * 480 / 287;
    data->point.y = state.TouchY * 272 / 153;
    data->state = LV_INDEV_STATE_PRESSED;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

static void print_callback(const char *value) { sos_debug_printf(value); }

void lvgl_config_start() {

  lv_log_register_print_cb(print_callback);
  lv_init();

  lvgl_api_initialize_filesystem();

  static lv_disp_draw_buf_t disp_buf = {};
  lv_disp_draw_buf_init(&disp_buf, (lv_color_t *)LCD_LAYER_0_ADDRESS,
                        (lv_color_t *)LCD_LAYER_1_ADDRESS,
                        LCD_DEFAULT_WIDTH * LCD_DEFAULT_HEIGHT);

  static lv_disp_drv_t disp_drv = {};
  lv_disp_drv_init(&disp_drv);   /*Basic initialization*/
  disp_drv.draw_buf = &disp_buf; /*Set an initialized buffer*/
  disp_drv.flush_cb = flush_callback;
  disp_drv.full_refresh = 1;
  disp_drv.hor_res = LCD_DEFAULT_WIDTH;
  disp_drv.ver_res = LCD_DEFAULT_HEIGHT;

  /*Register the driver and save the created display objects*/
  lv_disp_t * display = lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv = {};
  lv_indev_drv_init(&indev_drv);           /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;  /*See below.*/
  indev_drv.read_cb = touch_read_callback; /*See below.*/
  /*Register the driver in LVGL and save the created input device object*/
  lv_indev_drv_register(&indev_drv);

  themes_initialize();
}

int lvgl_get_theme(void *args) {
  lvgl_api_theme_request_t *request = args;
  request->descriptor = themes_get_theme(request->offset);
  if( request->descriptor == NULL ) {
    errno = EINVAL;
    return -1;
  }
  return 0;
}

void lvgl_config_initialize_display() {
  cortexm_svcall(svcall_init_hardware, NULL);
  // Clear the display
  memset((void *)LCD_LAYER_0_ADDRESS, 0xff, CONFIG_VIDEO_MEMORY_SIZE / 2);
  memset((void *)LCD_LAYER_1_ADDRESS, 0xff, CONFIG_VIDEO_MEMORY_SIZE / 2);
  cortexm_svcall(svcall_flush, (void *)LCD_LAYER_1_ADDRESS);
}

int lvgl_get_font(void *args) {
  lvgl_api_font_request_t *request = args;
  if (request->offset <
      sizeof(fonts_list) / sizeof(lvgl_api_font_descriptor_t)) {
    request->descriptor = fonts_list + request->offset;
    return 0;
  }

  request->descriptor = NULL;
  errno = EINVAL;
  return -1;
}

#endif
