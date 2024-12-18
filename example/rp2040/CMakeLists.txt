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
##include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/src/usb/)

#add_definitions("-DUSBD_MANUFACTORY=\"othermo\"")
#add_definitions("-DUSBD_SERIAL=\"0000\"")
#add_definitions("-DUSBD_CDC=\"Board CDC\"")
#add_definitions("-DUSBD_PRODUCT=\"RP2040 EMS\"")

add_definitions("-DPICO_STDIO_USB_ENABLE_RESET_VIA_VENDOR_INTERFACE=1")
add_definitions("-DPICO_STDIO_USB_RESET_INTERFACE_SUPPORT_RESET_TO_BOOTSEL=1")

#add_custom_command(
#   OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/Version.hpp"
#   COMMAND mkdir -p include
#   COMMAND echo "#pragma once" >  include/Version.hpp
#   COMMAND echo "#define GIT_VERSION \"${CMAKE_GIT_VERSION}\"" >> include/Version.hpp
#   WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
#   COMMENT "Create Version header"
#   VERBATIM
#)
#add_custom_target(version_include DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/include/Version.hpp")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
message(STATUS "Build Type: " ${CMAKE_BUILD_TYPE})

add_executable(modbus ${CMAKE_SOURCE_DIR}/main_SendRequest.cpp)

set_source_files_properties(${CMAKE_SOURCE_DIR}/main_SendRequest.cpp PROPERTIES COMPILE_FLAGS "-Wlogical-op -Wstrict-null-sentinel -Wno-psabi -Wduplicated-cond -Wduplicated-branches -Wrestrict -Wstrict-overflow=5 -fconcepts -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -fwrapv -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Woverloaded-virtual -Wredundant-decls -Wswitch-default -Wold-style-cast -Wsign-conversion -Wsign-promo -Wconversion -Wnull-dereference -Wdouble-promotion -Werror=ignored-qualifiers -std=c++20 -Wno-missing-requires -fexceptions")

##target_include_directories(firmware PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")
#add_dependencies(firmware)

pico_enable_stdio_usb(modbus 0)
pico_enable_stdio_uart(modbus 0)
pico_add_extra_outputs(modbus)

target_link_libraries(modbus pico_stdlib hardware_flash)
## TODO ^^ remove links
