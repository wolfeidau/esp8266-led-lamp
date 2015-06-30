FROM wolfeidau/esp8266-dev:1.1.0

# add all the SDK stuff to the PATH
ENV PATH=$PATH:/opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin

WORKDIR /project

# pass -v $(pwd):/project to "share" your source with the container.
VOLUME /project

# note this assumes that the user your logged into is uid 1000 which
# matches the ubuntu user inside the container.
USER ubuntu

