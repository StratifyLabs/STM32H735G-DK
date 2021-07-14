
#include <cortexm/task.h>
#include <sos/debug.h>
#include <sos/sos.h>
#include <stm32_config.h>
#include <stm32_types.h>

#include "config.h"
#include "debug_config.h"

#if ___debug
static UART_HandleTypeDef m_huart MCU_SYS_MEM;
#endif

#define DEBUG_LED_PORT GPIOC
#define DEBUG_LED_PINMASK (1 << 3)

void debug_initialize() {

  // set LED 1,7 as output
  GPIO_InitTypeDef gpio_init;
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Pin = DEBUG_LED_PINMASK;
  gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DEBUG_LED_PORT, &gpio_init);
  debug_disable_led();

#if ___debug
  __HAL_RCC_USART3_CLK_ENABLE();

  /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
  gpio_init.Pin = (1 << 8) | (1 << 9);
  gpio_init.Mode = GPIO_MODE_AF_PP;
  gpio_init.Pull = GPIO_PULLUP;
  gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &gpio_init);

  m_huart.Instance = USART3;
  m_huart.Init.BaudRate = 400000;
  m_huart.Init.WordLength = UART_WORDLENGTH_8B;
  m_huart.Init.StopBits = UART_STOPBITS_1;
  m_huart.Init.Parity = UART_PARITY_NONE;
  m_huart.Init.Mode = UART_MODE_TX_RX;
  m_huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  m_huart.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&m_huart);
#endif

#if 0
  const char message[] = "Hello\n";
  while(1){
    debug_write(message, sizeof(message)-1);
    cortexm_delay_ms(200);
  }
#endif
}

void debug_write(const void *buf, int nbyte) {
#if ___debug
  const u8 *cbuf = buf;
  for (int i = 0; i < nbyte; i++) {
    u8 c = cbuf[i];
    HAL_UART_Transmit(&m_huart, &c, 1, HAL_MAX_DELAY);
  }
#endif
}

void debug_enable_led() {
  HAL_GPIO_WritePin(DEBUG_LED_PORT, DEBUG_LED_PINMASK, GPIO_PIN_RESET);
}

void debug_disable_led() {
  HAL_GPIO_WritePin(DEBUG_LED_PORT, DEBUG_LED_PINMASK, GPIO_PIN_SET);
}

#define TRACE_COUNT 64
#define TRACE_FRAME_SIZE sizeof(link_trace_event_t)
#define TRACE_BUFFER_SIZE (sizeof(link_trace_event_t) * TRACE_COUNT)

static char trace_buffer[TRACE_FRAME_SIZE * TRACE_COUNT] DEBUG_TRACE_MEMORY;
const ffifo_config_t debug_trace_config = {.frame_count = TRACE_COUNT,
                                           .frame_size =
                                               sizeof(link_trace_event_t),
                                           .buffer = trace_buffer};
ffifo_state_t debug_trace_state DEBUG_TRACE_MEMORY;
u16 debug_trace_checksum DEBUG_TRACE_MEMORY;

static u16 get_checksum() {
  const u16 *check = (const u16 *)&debug_trace_state;
  u16 checksum = 0;
  for (size_t i = 0; i < sizeof(ffifo_state_t) / sizeof(u16); i++) {
    checksum += check[i];
  }
  return checksum;
}

void debug_trace_event(void *event) {
  link_trace_event_header_t *header = event;
  devfs_async_t async;
  const devfs_device_t *trace_dev = &(sos_config.fs.devfs_list[0]);


  const u16 checksum =get_checksum();
  // if the checksum is wrong -- reset the state
  if (checksum != debug_trace_checksum) {
    debug_trace_state = (ffifo_state_t){};
    debug_trace_checksum = get_checksum();
  }

  // write the event to the fifo
  memset(&async, 0, sizeof(devfs_async_t));
  async.tid = task_get_current();
  async.buf = event;
  async.nbyte = header->size;
  async.flags = O_RDWR;
  trace_dev->driver.write(&(trace_dev->handle), &async);

  debug_trace_checksum = get_checksum();

}
