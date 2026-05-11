FROM alpine:3.21.3

RUN apk update && \
    apk add \ 
    include-what-you-use \
    g++ \
    gcc \ 
    gcc-arm-none-eabi\    
    g++-arm-none-eabi \
    cmake \ 
    make \
    clang \
    clang-extra-tools \
    git \
    doxygen \
    py3-pip \
    py3-pytest \
    openocd \
    lcov\
    gdb \
    gdb-multiarch \
    gzip \ 
    allegro-dev \
    graphviz

RUN pip install protobuf grpcio-tools cmakelang --break-system-packages

RUN apk add curl libc6-compat
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/local/bin sh
RUN arduino-cli core --additional-urls=http://arduino.esp8266.com/stable/package_esp8266com_index.json install esp8266:esp8266
RUN arduino-cli lib install pubsubclient 
