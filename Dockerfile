#
# To use this first build an image with some tag, then use it to run your builds.
#
# docker build -t esp8266-build .
#
# docker run -v /Users:/Users -i -t esp8266-build make
#
FROM wolfeidau/esp8266-dev:1.2.0

# add all the SDK stuff to the PATH
ENV PATH=$PATH:/opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin

WORKDIR /Users/markw/Code/Systems/esp8266-led-lamp

VOLUME /Users

# note this assumes that the user your logged into is uid 1000 which
# matches the ubuntu user inside the container.
USER ubuntu

