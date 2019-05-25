#!/bin/bash

g++ -g -Wall -pedantic -l ncurses -o executable \
src/main.cpp \
src/graphics/window.cpp \
src/graphics/window_manager.cpp \
src/graphics/screen.cpp \
src/graphics/textbox.cpp \
src/utils/helpers.cpp \
src/graphics/button.cpp \
src/graphics/menu.cpp;
