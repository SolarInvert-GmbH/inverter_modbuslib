cmake_minimum_required(VERSION 3.4.3)

include_directories(${CMAKE_SOURCE_DIR}/example/include)

add_library(main_dummyinverter                                                      OBJECT   main_Dummy_Inverter.cpp                                                               )

add_executable(Dummy_Inverter                                                                    $<TARGET_OBJECTS:main_dummyinverter>                                                      )

target_link_libraries   (Dummy_Inverter fltk dl X11)
