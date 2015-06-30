FROM wolfeidau/esp8266-dev:1.1.0

ENV PATH=$PATH:/opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin

WORKDIR /project

VOLUME /project

USER ubuntu

