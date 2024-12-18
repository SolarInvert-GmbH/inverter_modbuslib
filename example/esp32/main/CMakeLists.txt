
set (SRCS "main_SendRequest.cpp")
idf_component_register(SRCS         "${SRCS}"
                       INCLUDE_DIRS "../../../include;../../../json/include;../../../random/include;../../../string/include;../../../modbus/include")

set(VAR "${VAR} -std=c++2a")
set(VAR "${VAR} -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -fwrapv")
set(VAR "${VAR} -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self")
set(VAR "${VAR} -Wmissing-declarations -Wmissing-include-dirs -Woverloaded-virtual")
set(VAR "${VAR} -Wredundant-decls -Wswitch-default -Wold-style-cast -Wsign-conversion")
set(VAR "${VAR} -Wsign-promo -Wconversion -Wnull-dereference -Wdouble-promotion")
set(VAR "${VAR} -Werror=ignored-qualifiers")
set(VAR "${VAR} -Wno-missing-requires")
set(VAR "${VAR} -fexceptions")
set(VAR "${VAR} -isystem $ENV{IDF_PATH}/components/")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
   set(VAR "${VAR} -Wlogical-op -Wstrict-null-sentinel -Wno-psabi -Wduplicated-cond")
   set(VAR "${VAR} -Wduplicated-branches -Wrestrict -Wstrict-overflow=5 -fconcepts")
endif()
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
   set(VAR "${VAR} -Wno-unused-private-field")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" LOWER_BUILD_TYPE)
if( "${LOWER_BUILD_TYPE}" STREQUAL "debug")
    set(VAR "${VAR} -O0")
else()
    set(VAR "${VAR} -O3 -Werror")
    set(VAR "${VAR} -Werror=unused-function -Werror=unused-variable -Werror=deprecated-declarations -Werror=unused-but-set-variable")
endif()

#set(VAR "${VAR} -DGIT_VERSION=\"\\\"0.0.0-435 b99e40475556b75093dbb33a3f88da91c6d019a8\\\"\"")

foreach (SRC IN LISTS SRCS)
    set_source_files_properties("${SRC}" PROPERTIES COMPILE_FLAGS ${VAR})
endforeach()
