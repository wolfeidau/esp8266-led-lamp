#include "ws2812.h"
#include "gpio.h"

// Other GPIO output pin can be set here
#define WS2812_GPIO 5

void SEND_WS_0()
{
    int i = 4;
    while(i--) // 4 high, approx. 400ns (250~550)
        GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS,1<<WS2812_GPIO); // W1TS = Write 1 to SET

    i = 9;
    while(i--) // 9 low, approx. 850ns (700~1000)
        GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS,1<<WS2812_GPIO); // W1TC = Write 1 to CLEAR
}

void SEND_WS_1()
{
    int i = 8;
    while(i--) // 8 high, approx. 800ns (650~950)
        GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS,1<<WS2812_GPIO);

    i = 5;
    while(i--) // 5 low, approx. 450ns (300~600)
        GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS,1<<WS2812_GPIO);
}

void WS2812OutBuffer( uint8_t * buffer, uint16_t length )
{
    uint16_t i;
    GPIO_OUTPUT_SET(GPIO_ID_PIN(WS2812_GPIO),0); // Setup the GPIO pin as output and initialize it to low.

    for( i = 0; i < length; i++ )
    {
        uint8_t byte = buffer[i];
        if( byte & 0x80 ) SEND_WS_1(); else SEND_WS_0();
        if( byte & 0x40 ) SEND_WS_1(); else SEND_WS_0();
        if( byte & 0x20 ) SEND_WS_1(); else SEND_WS_0();
        if( byte & 0x10 ) SEND_WS_1(); else SEND_WS_0();
        if( byte & 0x08 ) SEND_WS_1(); else SEND_WS_0();
        if( byte & 0x04 ) SEND_WS_1(); else SEND_WS_0();
        if( byte & 0x02 ) SEND_WS_1(); else SEND_WS_0();
        if( byte & 0x01 ) SEND_WS_1(); else SEND_WS_0();
    }
    // Reset will happen when it's low long enough.
    // Don't call this function twice within 10us.
}
