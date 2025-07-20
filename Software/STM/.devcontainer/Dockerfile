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
    allegro-dev

# cmake-format
RUN   pip install cmakelang --break-system-packages

