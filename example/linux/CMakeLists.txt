cmake_minimum_required(VERSION 3.4.3)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/example/linux/)

add_library(main_responder                                                          OBJECT   main_Responder.cpp                                                                    )
add_library(main_sendrequest                                                        OBJECT   main_SendRequest.cpp                                                                  )

add_executable(Responder                                                                         $<TARGET_OBJECTS:main_responder>                                                          )
add_executable(SendRequest                                                                       $<TARGET_OBJECTS:main_sendrequest>                                                        )

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.0)
        target_compile_options(main_responder   PUBLIC "-Wno-maybe-uninitialized")
        target_compile_options(main_sendrequest PUBLIC "-Wno-maybe-uninitialized")
    endif()
endif()

add_subdirectory(gui)
