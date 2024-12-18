cmake_minimum_required(VERSION 3.13)

include(../../config/pico_sdk_import.cmake)

project(rp2040_modbus C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

message(STATUS "Building rp2040 modbus [${CMAKE_GIT_VERSION}]")

include_directories(${CMAKE_SOURCE_DIR}/../../include)
include_directories(${CMAKE_SOURCE_DIR}/../../json/include/)
include_directories(${CMAKE_SOURCE_DIR}/../../random/include/)
include_directories(${CMAKE_SOURCE_DIR}/../../string/include/)
include_directories(${CMAKE_SOURCE_DIR}/../../modbus/include/)

include_directories(SYSTEM ${PICO_SDK_PATH}/src/rp2_common/)
include_directories(SYSTEM ${PICO_SDK_PATH}/src/common/)
include_directories(SYSTEM ${PICO_SDK_PATH}/src/rp2040/)
include_directories(SYSTEM ${PICO_SDK_PATH}/lib/)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
message(STATUS "Build Type: " ${CMAKE_BUILD_TYPE})

add_executable(modbus ${CMAKE_SOURCE_DIR}/main_SendRequest.cpp)

set_source_files_properties(${CMAKE_SOURCE_DIR}/main_SendRequest.cpp PROPERTIES COMPILE_FLAGS "-Wlogical-op -Wstrict-null-sentinel -Wno-psabi -Wduplicated-cond -Wduplicated-branches -Wrestrict -Wstrict-overflow=5 -fconcepts -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -fwrapv -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Woverloaded-virtual -Wredundant-decls -Wswitch-default -Wold-style-cast -Wsign-conversion -Wsign-promo -Wconversion -Wnull-dereference -Wdouble-promotion -Werror=ignored-qualifiers -std=c++20 -Wno-missing-requires -fexceptions")

pico_enable_stdio_usb(modbus 0)
pico_enable_stdio_uart(modbus 0)
pico_add_extra_outputs(modbus)

target_link_libraries(modbus pico_stdlib)
