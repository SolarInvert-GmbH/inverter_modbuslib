cmake_minimum_required(VERSION 3.5)

include_directories(${CMAKE_SOURCE_DIR}/example/include)

add_library(main_dummyinverter                                                      OBJECT   main_Dummy_Inverter.cpp                                                               )
add_library(main_miniSICC                                                           OBJECT   main_miniSICC.cpp                                                                     )

add_executable(Dummy_Inverter                                                                    $<TARGET_OBJECTS:main_dummyinverter>                                                      )
add_executable(miniSICC                                                                          $<TARGET_OBJECTS:main_miniSICC>                                                           )

find_package(PkgConfig REQUIRED)

pkg_check_modules(CAIRO REQUIRED cairo)

target_include_directories(main_dummyinverter PRIVATE ${CAIRO_INCLUDE_DIRS})
target_include_directories(main_miniSICC      PRIVATE ${CAIRO_INCLUDE_DIRS})

target_link_libraries   (Dummy_Inverter fltk cairo )
target_link_libraries   (miniSICC fltk cairo)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.0)
        target_compile_options(main_dummyinverter   PUBLIC "-Wno-maybe-uninitialized")
        target_compile_options(main_miniSICC        PUBLIC "-Wno-maybe-uninitialized")
    endif()
endif()

install(TARGETS Dummy_Inverter RUNTIME DESTINATION bin)
install(TARGETS miniSICC       RUNTIME DESTINATION bin)
