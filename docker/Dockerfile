FROM ubuntu:24.04

ARG ESP_IDF_TAG="v5.2"
ARG FLTK_TAG="release-1.4.1"
ARG PICO_SDK="2.1.0"


RUN apt-get update && apt-get install -y --no-install-recommends ssh git cmake python3 pip gcc g++ curl ca-certificates doxygen graphviz gcovr libdebuginfod-dev libusb-1.0-0 make python3.12-venv mingw-w64 gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev && apt-get autoremove && rm -rf /var/lib/apt/lists/*


RUN cd / && git clone https://github.com/espressif/esp-idf.git && cd /esp-idf && git checkout ${ESP_IDF_TAG} && /esp-idf/install.sh && ./tools/set-submodules-to-github.sh && git submodule update --init

RUN cd / && git clone https://github.com/fltk/fltk.git && cd /fltk && git checkout ${FLTK_TAG} && mkdir build && cd build && cmake .. && make install  && cd / && rm -r /fltk

ARG MINGW_CMAKE="set(CMAKE_SYSTEM_NAME Windows)\nset(TOOLCHAIN_PREFIX x86_64-w64-mingw32)\nset(CMAKE_C_COMPILER \${TOOLCHAIN_PREFIX}-gcc)\nset(CMAKE_CXX_COMPILER \${TOOLCHAIN_PREFIX}-g++)\nset(CMAKE_Fortran_COMPILER \${TOOLCHAIN_PREFIX}-gfortran)\nset(CMAKE_RC_COMPILER \${TOOLCHAIN_PREFIX}-windres)\nset(CMAKE_FIND_ROOT_PATH /usr/\${TOOLCHAIN_PREFIX})\nset(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)\nset(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)\nset(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)\n"

ARG MINGW_PATH="/usr/lib/gcc/x86_64-w64-mingw32/13-win32/"

RUN cd / && git clone https://github.com/fltk/fltk.git && cd /fltk && git checkout ${FLTK_TAG} && printf "${MINGW_CMAKE}" > mingw.cmake && mkdir build && cd build && cmake -DCMAKE_TOOLCHAIN_FILE=../mingw.cmake .. && make && cp -r ../FL "${MINGW_PATH}/include" && cp ./FL/fl_config.h "${MINGW_PATH}/include/FL" && cp -r ./lib/. "${MINGW_PATH}" && cd / && rm -r /fltk

ENV PICO_SDK_PATH="/pico-sdk"

RUN cd / && git clone https://github.com/raspberrypi/pico-sdk.git && cd pico-sdk && git checkout tags/${PICO_SDK} && git submodule update --init
