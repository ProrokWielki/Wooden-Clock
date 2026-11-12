FROM alpine:3.23.5

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
    graphviz \
    gcompat \ 
    protobuf \
    openjdk8-jre \
    black \
    py3-flake8 \
    ruff

RUN pip install protobuf grpcio-tools cmakelang platformio readelf --break-system-packages
