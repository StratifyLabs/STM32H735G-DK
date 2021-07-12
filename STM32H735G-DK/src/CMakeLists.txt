
set(SOURCES
	config.h
	sl_config.h
	config/clock_config.c
	config/clock_config.h
	config/cache_config.c
	config/cache_config.h
	config/debug_config.c
	config/debug_config.h
	config/sleep_config.c
	config/sleep_config.h
	config/sys_config.c
	config/sys_config.h
	config/devfs_config.c
	config/devfs_config.h
	config/fs_config.c
	config/fs_config.h
	config/link_config.c
	config/link_config.h
	config/mcu_config.c
	config/mcu_config.h
	config/os_config.c
	config/os_config.h
	config/usb_config.c
	config/usb_config.h
	config/stm32_config.c
	config/sos_config.c
	config/symbols_config.c

	config/lvgl_config.c
	config/lvgl_config.h

	stm32/SystemClock_config.c

	stm32/stm32h735g_discovery_audio.c
	stm32/stm32h735g_discovery_audio.h

	stm32/stm32h735g_discovery_lcd.c
	stm32/stm32h735g_discovery_lcd.h
	stm32/stm32h735g_discovery_ospi.c
	stm32/stm32h735g_discovery_ospi.h
	stm32/stm32h735g_discovery_bus.c
	stm32/stm32h735g_discovery_bus.h
	#stm32/stm32h735g_discovery_sd.c
	#stm32/stm32h735g_discovery_sd.h
	stm32/stm32h735g_discovery_ts.c
	stm32/stm32h735g_discovery_ts.h
	stm32/stm32h735g_discovery_errno.h
	stm32/stm32h735g_discovery_conf.h

	stm32/mx25lm51245g/mx25lm51245g.c
	stm32/mx25lm51245g/mx25lm51245g.h
	stm32/mx25lm51245g/mx25lm51245g_conf.h

	stm32/s70kl1281/s70kl1281.c
	stm32/s70kl1281/s70kl1281.h
	stm32/s70kl1281/s70kl1281_conf.h

	stm32/ft5336/ft5336.c
	stm32/ft5336/ft5336.h
	stm32/ft5336/ft5336_reg.c
	stm32/ft5336/ft5336_reg.h
	stm32/ft5336/ft5336_conf.h

	stm32/wm8994/wm8994.c
	stm32/wm8994/wm8994.h
	stm32/wm8994/wm8994_reg.c
	stm32/wm8994/wm8994_reg.h

	stm32/rk043fn48h/rk043fn48h.h

	stm32/pdm2pcm_glo.h
	stm32/audio.h
	stm32/lcd.h
	stm32/ts.h
	stm32/stm32h735g-dk.c
	stm32/stm32h735g-dk.h


	PARENT_SCOPE)
