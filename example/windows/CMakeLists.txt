cmake_minimum_required(VERSION 3.4.3)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/example/windows/)

add_library(main_sendrequest                                                        OBJECT   main_SendRequest.cpp                                                                  )

add_executable(SendRequest                                                                       $<TARGET_OBJECTS:main_sendrequest>                                                        )
