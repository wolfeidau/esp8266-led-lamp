#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "mem.h"
#include "user_interface.h"
#include "dht.h"

#include "espconn.h"

LOCAL struct espconn ptrespconn;

void ICACHE_FLASH_ATTR
user_devicefind_recv(void *arg, char *pusrdata, unsigned short length)
{

    os_printf("recieved data: %d\n", length);
    os_printf("data: %s\n", pusrdata);

    struct sensor_reading* result = readDHT(0);

    os_printf("humidity: %d temperature: %d success: %d\n", (int)(result->humidity), (int)(result->temperature), result->success);
 //    char DeviceBuffer[40] = {0};
 //    char Device_mac_buffer[60] = {0};
 //    char hwaddr[6];

 //    struct ip_info ipconfig;

 //    if (wifi_get_opmode() != STATION_MODE) {
 //        wifi_get_ip_info(SOFTAP_IF, &ipconfig);
 //        wifi_get_macaddr(SOFTAP_IF, hwaddr);

 //        if (!ip_addr_netcmp((struct ip_addr *)ptrespconn.proto.udp->remote_ip, &ipconfig.ip, &ipconfig.netmask)) {
 //            wifi_get_ip_info(STATION_IF, &ipconfig);
 //            wifi_get_macaddr(STATION_IF, hwaddr);
 //        }
 //    } else {
 //        wifi_get_ip_info(STATION_IF, &ipconfig);
 //        wifi_get_macaddr(STATION_IF, hwaddr);
 //    }

 //    if (pusrdata == NULL) {
 //        return;
 //    }

	// os_sprintf(DeviceBuffer, "%s" MACSTR " " IPSTR,	MAC2STR(hwaddr), IP2STR(&ipconfig.ip));

	// os_printf("%s\n", DeviceBuffer);
	// length = os_strlen(DeviceBuffer);
	// espconn_sent(&ptrespconn, DeviceBuffer, length);

    // if (length == os_strlen(device_find_request) &&
    //         os_strncmp(pusrdata, device_find_request, os_strlen(device_find_request)) == 0) {
    //     os_sprintf(DeviceBuffer, "%s" MACSTR " " IPSTR, device_find_response_ok,
    //                MAC2STR(hwaddr), IP2STR(&ipconfig.ip));

    //     os_printf("%s\n", DeviceBuffer);
    //     length = os_strlen(DeviceBuffer);
    //     espconn_sent(&ptrespconn, DeviceBuffer, length);
    // } else if (length == (os_strlen(device_find_request) + 18)) {
    //     os_sprintf(Device_mac_buffer, "%s " MACSTR , device_find_request, MAC2STR(hwaddr));
    //     os_printf("%s", Device_mac_buffer);

    //     if (os_strncmp(Device_mac_buffer, pusrdata, os_strlen(device_find_request) + 18) == 0) {
    //         //os_printf("%s\n", Device_mac_buffer);
    //         length = os_strlen(DeviceBuffer);
    //         os_sprintf(DeviceBuffer, "%s" MACSTR " " IPSTR, device_find_response_ok,
    //                    MAC2STR(hwaddr), IP2STR(&ipconfig.ip));

    //         os_printf("%s\n", DeviceBuffer);
    //         length = os_strlen(DeviceBuffer);
    //         espconn_sent(&ptrespconn, DeviceBuffer, length);
    //     } else {
    //         return;
    //     }
    // }
}

// user device location which responds to a simple broadcast.
void ICACHE_FLASH_ATTR
user_devicefind_init(void)
{
    ptrespconn.type = ESPCONN_UDP;
    ptrespconn.proto.udp = (esp_udp *)os_zalloc(sizeof(esp_udp));
    ptrespconn.proto.udp->local_port = 2534;
    espconn_regist_recvcb(&ptrespconn, user_devicefind_recv);
    espconn_create(&ptrespconn);
}
