/**
  ******************************************************************************
  * @file    stm32h735g_discovery_conf.h
  * @author  MCD Application Team
  * @brief   STM32H735G_DISCO board configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H735G_DK_CONF_H
#define STM32H735G_DK_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stm32h7xx.h>
#include <stm32h7xx/stm32h7xx_hal_dma.h>
#include <stm32h7xx/stm32h7xx_hal_dma2d.h>
#include <stm32h7xx/stm32h7xx_hal_cortex.h>
#include <stm32h7xx/stm32h7xx_hal_gpio.h>
#include <stm32h7xx/stm32h7xx_hal_sai.h>
#include <stm32h7xx/stm32h7xx_hal_i2s.h>
#include <stm32h7xx/stm32h7xx_hal_rcc.h>
#include <stm32h7xx/stm32h7xx_hal_rcc_ex.h>
#include <stm32h7xx/stm32h7xx_hal_dfsdm.h>
#include <stm32h7xx/stm32h7xx_hal_ltdc.h>
#include <stm32h7xx/stm32h7xx_hal_i2c.h>
#include <stm32h7xx/stm32h7xx_hal_exti.h>
#include <stm32h7xx/stm32h7xx_hal_exti.h>
#include <stm32h7xx/stm32h7xx_hal_sd.h>


/* COM define */
#define USE_COM_LOG                         0U
#define USE_BSP_COM_FEATURE                 0U

/* I2C BUS timing define */
#define I2C_VALID_TIMING_NBR                128U

/* Audio codecs defines */
#define USE_AUDIO_CODEC_WM8994              1U
#define USE_BSP_PDM_LIB_FEATURE             1U

/* Default Audio IN internal buffer size */
#define DEFAULT_AUDIO_IN_BUFFER_SIZE        2048U
#define USE_BSP_CPU_CACHE_MAINTENANCE       1U

/* LCD defines */
#define LCD_LAYER_0_ADDRESS                 0x70000000U
#define LCD_LAYER_1_ADDRESS                 0x70200000U
#define USE_DMA2D_TO_FILL_RGB_RECT          0U
#define USE_LCD_CTRL_RK043FN48H             1U

/* TS defines */
#define USE_TS_GESTURE                      1U
#define USE_TS_MULTI_TOUCH                  1U
#define TS_TOUCH_NBR                        2U

/* OSPI RAM interrupt priority */
#define BSP_OSPI_RAM_IT_PRIORITY            0x07UL
#define BSP_OSPI_RAM_DMA_IT_PRIORITY        0x07UL

/* IRQ priorities */
#define BSP_BUTTON_USER_IT_PRIORITY         15U
#define BSP_AUDIO_OUT_IT_PRIORITY           14U
#define BSP_AUDIO_IN_IT_PRIORITY            15U
#define BSP_SD_IT_PRIORITY                  14U
#define BSP_SD_RX_IT_PRIORITY               14U
#define BSP_SD_TX_IT_PRIORITY               15U
#define BSP_TS_IT_PRIORITY                  15U

#ifdef __cplusplus
}
#endif

#endif /* STM32H735G_DK_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
