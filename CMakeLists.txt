cmake_minimum_required(VERSION 3.0)

project(Gamebook VERSION 0.9 LANGUAGES C CXX)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
add_library(Gamebook SHARED src/graphics/button.cpp
        src/graphics/menu.cpp
        src/graphics/screen.cpp
        src/graphics/textbox.cpp
        src/graphics/window.cpp
        src/graphics/window_manager.cpp
        src/utils/helpers.cpp
        src/utils/rng.cpp
        src/utils/xml_parser.cpp)
