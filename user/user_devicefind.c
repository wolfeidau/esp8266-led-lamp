#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "mem.h"
#include "user_interface.h"
#include "dht.h"
#include "coap.h"

#include "espconn.h"

LOCAL struct espconn ptrespconn;

uint8_t packetbuf[256];
static uint8_t scratch_raw[32];
static coap_rw_buffer_t scratch_buf = {scratch_raw, sizeof(scratch_raw)};

void ICACHE_FLASH_ATTR
user_devicefind_recv(void *arg, char *pusrdata, unsigned short length)
{

    int rc;
    coap_packet_t pkt;

    os_printf("recieved data: %d\n", length);
    //os_printf("data: %s\n", pusrdata);

//    struct sensor_reading* result = readDHT(0);

//    os_printf("humidity: %d temperature: %d success: %d\n", (int)(result->humidity), (int)(result->temperature), result->success);

    if (0 != (rc = coap_parse(&pkt, pusrdata, length))) {
        os_printf("bad packet: rc=%d\n", rc);
    } else {
        size_t rsplen = sizeof(packetbuf);
        coap_packet_t rsppkt;

        coap_handle_req(&scratch_buf, &pkt, &rsppkt);

        memset(packetbuf, 0, 256);

        if (0 != (rc = coap_build(packetbuf, &rsplen, &rsppkt))) {
            os_printf("coap_build: rc=%d\n", rc);
        } else {
            espconn_sent(&ptrespconn, packetbuf, rsplen);
        }

    }

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
