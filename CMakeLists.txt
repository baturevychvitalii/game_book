cmake_minimum_required(VERSION 3.0)

project(Gamebook VERSION 0.9 LANGUAGES C CXX)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wpedantic -O2")

set(LIBRARY_SOURCE_FILES src/graphics/button.cpp
        src/graphics/menu.cpp
        src/graphics/screen.cpp
        src/graphics/textbox.cpp
        src/graphics/window.cpp
        src/graphics/window_manager.cpp
        src/utils/helpers.cpp)

add_library(gamebook SHARED ${LIBRARY_SOURCE_FILES})

target_link_libraries(gamebook ${CURSES_LIBRARIES})
add_executable(demonstrator src/main.cpp)
target_link_libraries(demonstrator gamebook)