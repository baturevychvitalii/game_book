cmake_minimum_required(VERSION 3.0)

project(Gamebook VERSION 1.0 LANGUAGES C CXX)

#find required libraries
find_package(Curses REQUIRED)
find_package(LibXml2 REQUIRED)

#include library directories
include_directories(${CURSES_INCLUDE_DIRS} ${LIBXML2_INCLUDE_DIR})

#set compiling properties
set(CMAKE_CXX_STANDARD 14)

#Release
#set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -O2")
#Debug
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wpedantic ")


#select sources for game book library
set(LIBRARY_SOURCE_FILES
        src/game_book/items/food.cpp
        src/game_book/items/fixer.cpp
        src/game_book/items/weapon.cpp
        src/game_book/page_types/combat.cpp
        src/game_book/page_types/story.cpp
        src/game_book/page_types/trade.cpp
        src/game_book/creature.cpp
        src/game_book/inventory.cpp
        src/game_book/item.cpp
        src/game_handler/colors.cpp
        src/game_handler/game_state_manager.cpp
        src/game_handler/IGameState.cpp
        src/game_handler/inventory_state.cpp
        src/game_handler/main_menu.cpp
        src/game_handler/page_state.cpp
        src/game_handler/pause_state.cpp
        src/utils/graphics/button.cpp
        src/utils/graphics/screen.cpp
        src/utils/graphics/status_bar.cpp
        src/utils/graphics/textbox.cpp
        src/utils/graphics/window.cpp
        src/utils/graphics/window_manager.cpp
        src/utils/xml_parser/document.cpp
        src/utils/xml_parser/tag.cpp
        src/utils/xml_parser/xml_exception.cpp
        src/utils/xml_parser/xml_parser.cpp
        src/utils/helpers.cpp
        src/utils/rng.cpp)

#create game book library
add_library(gamebook SHARED ${LIBRARY_SOURCE_FILES})

#link created library with external libraries
target_link_libraries(gamebook ${CURSES_LIBRARIES} ${LIBXML2_LIBRARIES})

#create executable file
add_executable(demonstrator src/main.cpp)

#link executable file and game book library
target_link_libraries(demonstrator gamebook)

