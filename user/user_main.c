#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"

// entry of user application
void ICACHE_FLASH_ATTR
user_init(void)
{
    os_printf("SDK version:%s\n", system_get_sdk_version());
}