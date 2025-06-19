cmake_minimum_required(VERSION 3.4.3)

include_directories(${CMAKE_SOURCE_DIR}/example/include)

add_library(main_dummyinverter                                                      OBJECT   main_Dummy_Inverter.cpp                                                               )
add_library(main_miniSICC                                                           OBJECT   main_miniSICC.cpp                                                                     )

add_executable(Dummy_Inverter                                                                    $<TARGET_OBJECTS:main_dummyinverter>                                                      )
add_executable(miniSICC                                                                          $<TARGET_OBJECTS:main_miniSICC>                                                           )

target_link_libraries  (Dummy_Inverter fltk gdiplus comctl32 ws2_32 winspool uuid comdlg32)
target_link_libraries  (miniSICC       fltk gdiplus comctl32 ws2_32 winspool uuid comdlg32 wbemuuid)
