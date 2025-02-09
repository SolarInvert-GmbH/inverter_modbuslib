cmake_minimum_required(VERSION 3.4.3)

include_directories(${CMAKE_SOURCE_DIR}/example/include)

add_library(main_dummyinverter                                                      OBJECT   main_Dummy_Inverter.cpp                                                               )

add_executable(Dummy_Inverter                                                                    $<TARGET_OBJECTS:main_dummyinverter>                                                      )

target_link_libraries   (Dummy_Inverter fltk dl SM ICE X11 Xext Xinerama Xfixes Xcursor Xrender pango-1.0 pangocairo-1.0 gobject-2.0 glib-2.0 harfbuzz cairo pangoxft-1.0 pangoft2-1.0 fontconfig freetype Xft wayland-egl wayland-client EGL gtk-3 gdk-3 z atk-1.0 cairo-gobject gdk_pixbuf-2.0 gio-2.0 wayland-cursor xkbcommon dbus-1)
