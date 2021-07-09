
#include <lvgl.h>
#include <lvgl_api.h>
#include <sos/config.h>

#include "os_config.h"

#include "stm32/stm32h735g_discovery_conf.h"
#include "stm32/stm32h735g_discovery_lcd.h"

#if _IS_BOOT == 0

static lv_disp_draw_buf_t disp_buf;
static lv_disp_drv_t disp_drv;

#define VIDEO_MEM_SIZE (LCD_DEFAULT_WIDTH * LCD_DEFAULT_HEIGHT * 2)

/*Static or global buffer(s). The second buffer is optional*/

void lvgl_config_root_set_video_memory(void *address) {

  sos_config.cache.invalidate_data_block(address, VIDEO_MEM_SIZE);

  BSP_LCD_LayerConfig_t config = {};
  config.X1 = LCD_DEFAULT_WIDTH;
  config.Y1 = LCD_DEFAULT_HEIGHT;
  config.PixelFormat = LCD_PIXEL_FORMAT_RGB565;
  config.Address = (u32)address;
  BSP_LCD_ConfigLayer(0, 0, &config);
}

static void svcall_clean_cache(void *args) { CORTEXM_SVCALL_ENTER(); }

static void svcall_flush(void *args) {
  CORTEXM_SVCALL_ENTER();

  // invalidate the cache

  // just need to point the LCD to the new memory pointer
  lvgl_config_root_set_video_memory(args);
  SOS_DEBUG_LINE_TRACE();
}

static void flush_callback(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                           lv_color_t *color_p) {

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

static void touch_read_callback(lv_indev_drv_t *drv, lv_indev_data_t *data) {
  MCU_UNUSED_ARGUMENT(drv);
  MCU_UNUSED_ARGUMENT(data);
}

static void *tick_thread(void *args) {
  MCU_UNUSED_ARGUMENT(args);

  lv_obj_t *tv = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, LV_PCT(5));
  lv_tabview_add_tab(tv, "Tab1");
  lv_tabview_add_tab(tv, "Tab2");
  lv_tabview_add_tab(tv, "Tab3");

  while (1) {
    usleep(5 * 1000); /*Sleep for 5 millisecond*/
    lv_tick_inc(5);   /*Tell LVGL that 5 milliseconds were elapsed*/
    lv_timer_handler();
  }
}

static void print_callback(const char *value) { sos_debug_printf(value); }

void lvgl_config_init() {

  lv_log_register_print_cb(print_callback);
  lvgl_api_initialize();

  /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL
   * instead buf_2 */
  lv_disp_draw_buf_init(&disp_buf, (lv_color_t *)LCD_LAYER_0_ADDRESS,
                        (lv_color_t *)LCD_LAYER_1_ADDRESS,
                        LCD_DEFAULT_WIDTH * LCD_DEFAULT_HEIGHT);

  lv_disp_drv_init(&disp_drv);   /*Basic initialization*/
  disp_drv.draw_buf = &disp_buf; /*Set an initialized buffer*/
  disp_drv.flush_cb = flush_callback;
  disp_drv.full_refresh = 1;
  disp_drv.hor_res = LCD_DEFAULT_WIDTH;
  disp_drv.ver_res = LCD_DEFAULT_HEIGHT;

  lv_disp_t *disp;
  /*Register the driver and save the created display objects*/
  disp = lv_disp_drv_register(&disp_drv);

  lv_indev_drv_t indev_drv = {0};
  //lv_indev_drv_init(&indev_drv);           /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;  /*See below.*/
  indev_drv.read_cb = touch_read_callback; /*See below.*/
  /*Register the driver in LVGL and save the created input device object*/
  //lv_indev_t *my_indev = lv_indev_drv_register(&indev_drv);

  lv_area_t area = {};

  // point to the blank screen
  memset((void *)LCD_LAYER_1_ADDRESS, 0,
         LCD_DEFAULT_WIDTH * LCD_DEFAULT_HEIGHT * 2);
  flush_callback(&disp_drv, &area, (lv_color_t *)LCD_LAYER_1_ADDRESS);

  os_start_thread(tick_thread, NULL, 4096, SCHED_FIFO, 5);
}

#endif
