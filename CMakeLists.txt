cmake_minimum_required(VERSION 3.5)
project(cattalib)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message(STATUS "Building modbus lib [${CMAKE_GIT_VERSION}]")

add_compile_options(-std=c++20)

add_compile_options(
    -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -fwrapv
    -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self
    -Wmissing-declarations -Wmissing-include-dirs -Woverloaded-virtual
    -Wredundant-decls -Wswitch-default -Wold-style-cast -Wsign-conversion
    -Wsign-promo -Wconversion -Wnull-dereference -Wdouble-promotion
    -Werror=ignored-qualifiers)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    add_compile_options(-Wlogical-op -Wstrict-null-sentinel -Wno-psabi -Wduplicated-cond -Wduplicated-branches -Wrestrict)
    add_compile_options(-Wstrict-overflow=5)
    add_compile_options(-fconcepts)
    add_compile_options(-Wno-missing-requires)
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    add_compile_options(-Wno-unused-private-field)
endif()

if("${CMAKE_COVERAGE}" STREQUAL "true")
    set(CMAKE_COVERAGE_FLAG "--coverage")
    message(STATUS "Use coverage flag")
else()
    set(CMAKE_COVERAGE_FLAG "")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2 ${CMAKE_COVERAGE_FLAG} -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 ${CMAKE_COVERAGE_FLAG} -ggdb -fsanitize=address -fsanitize=undefined")
message(STATUS "Build Type: " ${CMAKE_BUILD_TYPE})

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/random/include/)
include_directories(${CMAKE_SOURCE_DIR}/string/include/)

add_subdirectory(test/unit)
