#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"
#include "dht.h"
#include "coap.h"

#include "os_type.h"
#include "user_config.h"
#include "user_interface.h"
#include "ws2812.h"

// entry of user application
void ICACHE_FLASH_ATTR
user_init(void)
{
    uart_init(BIT_RATE_115200, BIT_RATE_115200);

    os_printf("SDK version: %s\n", system_get_sdk_version());
    os_printf("Free Heap: %d\n", system_get_free_heap_size());
    os_printf("CPU Freq: %d\n", system_get_cpu_freq());

    user_devicefind_init();

    char ssid[32] = SSID;
    char password[64] = SSID_PASSWORD;
    struct station_config stationConf;

    //Set station mode
    wifi_set_opmode( 0x1 );

    //Set ap settings
    os_memcpy(&stationConf.ssid, ssid, 32);
    os_memcpy(&stationConf.password, password, 64);
    wifi_station_set_config(&stationConf);

    // DHTInit(SENSOR_DHT22, 30000);
    //WS2812Init();

    ets_wdt_disable();

    char outbuffer[] = {
        0x0f, 0x0f, 0xff,
        0x0f, 0x0f, 0xff,
        0x0f, 0x0f, 0xff,
        0x0f, 0x0f, 0xff,
        0x0f, 0x0f, 0xff,
        0x0f, 0x0f, 0xff,
        0x0f, 0x0f, 0xff,
        0x0f, 0x0f, 0xff
    };

    WS2812OutBuffer( outbuffer, 24 ); //Initialize the output.
}
