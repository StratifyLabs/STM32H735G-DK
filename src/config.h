
#ifndef CONFIG_H_
#define CONFIG_H_

#include <sos/arch.h>
#include <sos/debug.h>

#include "config/os_config.h"
#include "sl_config.h"

#define CONFIG_SYSTEM_MEMORY_SIZE (32 * 1024)
#define CONFIG_STDIO_BUFFER_SIZE 512
#define CONFIG_SYSTEM_CLOCK 100000000

// Total number of tasks (threads) for the entire system
#define CONFIG_TASK_TOTAL 16


#endif /* CONFIG_H_ */
