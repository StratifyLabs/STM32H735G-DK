#ifndef STM32H735GDK_H
#define STM32H735GDK_H

void SystemClock_Config();

//OSPI RAM is init'd by LCD so no need to call both of these
void stm32h735g_dk_init_ospi_ram();

#endif // STM32H735GDK_H
