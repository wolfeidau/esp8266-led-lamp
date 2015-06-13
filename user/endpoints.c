#include "ets_sys.h"
#include "osapi.h"
#include <c_types.h>
#include <string.h>
#include "coap.h"
#include "ws2812.h"
#include <stdio.h>

// we are controlling n leds with 3 colors
#define LED_BUFFER_SIZE 24

static char light = '1';
static uint8_t buffer[LED_BUFFER_SIZE];

const uint16_t rsplen = 1500;
static char rsp[1500] = "";
void build_rsp(void);

void endpoint_setup(void)
{
    // clear the buffer between writes
    memset(&buffer[0], 0, sizeof(buffer));

    build_rsp();
}

static const coap_endpoint_path_t path_well_known_core = {2, {".well-known", "core"}};
static int handle_get_well_known_core(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    return coap_make_response(scratch, outpkt, (const uint8_t *)rsp, strlen(rsp), id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_APPLICATION_LINKFORMAT);
}

static const coap_endpoint_path_t path_light = {1, {"light"}};
static int handle_get_light(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    return coap_make_response(scratch, outpkt, (const uint8_t *)&buffer[0], LED_BUFFER_SIZE, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_OCTET_STREAM);
}

static int handle_put_light(coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    int c = 0;

    // as we require 24 bytes of information to update the lights
    if (inpkt->payload.len != LED_BUFFER_SIZE)
        return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_BAD_REQUEST, COAP_CONTENTTYPE_OCTET_STREAM);

    // convert the payload to the types required in the WS2812 code
    // TODO: may be better to make these match
    for (c = 0; c < inpkt->payload.len; c++) {
        buffer[c] = (uint8_t)inpkt->payload.p[c];
    }

    WS2812OutBuffer(buffer, inpkt->payload.len);
    return coap_make_response(scratch, outpkt, (const uint8_t *)&buffer[0], LED_BUFFER_SIZE, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CHANGED, COAP_CONTENTTYPE_OCTET_STREAM);
}

const coap_endpoint_t endpoints[] =
{
    {COAP_METHOD_GET, handle_get_well_known_core, &path_well_known_core, "ct=40"},
    {COAP_METHOD_GET, handle_get_light, &path_light, "ct=0"},
    {COAP_METHOD_PUT, handle_put_light, &path_light, NULL},
    {(coap_method_t)0, NULL, NULL, NULL}
};

void ICACHE_FLASH_ATTR build_rsp(void)
{
    uint16_t len = rsplen;
    const coap_endpoint_t *ep = endpoints;
    int i;

    len--; // Null-terminated string

    while(NULL != ep->handler)
    {
        if (NULL == ep->core_attr) {
            ep++;
            continue;
        }

        if (0 < strlen(rsp)) {
            strncat(rsp, ",", len);
            len--;
        }

        strncat(rsp, "<", len);
        len--;

        for (i = 0; i < ep->path->count; i++) {
            strncat(rsp, "/", len);
            len--;

            strncat(rsp, ep->path->elems[i], len);
            len -= strlen(ep->path->elems[i]);
        }

        strncat(rsp, ">;", len);
        len -= 2;

        strncat(rsp, ep->core_attr, len);
        len -= strlen(ep->core_attr);

        ep++;
    }
}

