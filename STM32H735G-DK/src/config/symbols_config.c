
#include "config.h"

#if _IS_BOOT == 0
#include <sos/symbols.h>
#include <sos/symbols/table.h>
#else
u32 const symbols_table[] = { 0x0 };
#endif
