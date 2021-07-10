
#include "config.h"

#include "stm32h735g-dk.h"

#include "stm32h735g_discovery_lcd.h"
#include "stm32h735g_discovery_ospi.h"


void stm32h735g_dk_init_ospi_ram() {
  BSP_OSPI_RAM_Init_t ospi_ram_init = {};
  /* Initialize the OSPI Hyper RAM memory */
  ospi_ram_init.LatencyType = BSP_OSPI_RAM_FIXED_LATENCY;
  ospi_ram_init.BurstType = BSP_OSPI_RAM_LINEAR_BURST;
  ospi_ram_init.BurstLength = BSP_OSPI_RAM_BURST_32_BYTES;
  BSP_OSPI_RAM_Init(0, &ospi_ram_init);
  BSP_OSPI_RAM_EnableMemoryMappedMode(0);
}


void mcu_core_octospi1_isr(){
  BSP_OSPI_RAM_IRQHandler(0);
}

void mcu_core_octospi2_isr(){
  BSP_OSPI_RAM_IRQHandler(1);
}
