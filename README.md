# led-lamp

Building a LED lamp using esp8266 and some ws2812s and a temperature/humidity sensor.

# overview

Parts I am using at the moment are:

* [NodeMCU v2 esp8266 board](http://tronixlabs.com/wireless/esp8266/nodemcu-v2-lua-based-esp8266-development-kit/)
* [WS2812 leds](http://tronixlabs.com/components/leds/neopixel/adafruit-neopixel-stick-8-x-ws2812-5050-rgb-led-with-integrated-drivers-australia/)
* [DHT11 temperature/humidity sensor](http://tronixlabs.com/sensors/humidity/dht11-temperature-and-humidity-sensor/)

![Picture of the project](/docs/images/IMG_0181.jpg)

# schematic

TODO

# building

Create a new `include/user_config.h` containing the following.

```
#define SSID "XXX"
#define SSID_PASSWORD "XXXX"
```

Then build the project.

```
make
```

# flashing

```
make flash
```

# Reference

![NodeMCU v2 board pinouts](/docs/images/NodeMCU_Pinout.png)

# License

This code is Copyright (c) 2014 Mark Wolfe and licenced under the MIT licence.
