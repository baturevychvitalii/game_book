#!/bin/bash

g++ -g -Wall -pedantic \
-l ncurses \
-I/usr/include/libxml2 \
-l xml2 \
-o executable \
src/main.cpp \
src/utils/graphics/window.cpp \
src/utils/graphics/window_manager.cpp \
src/utils/graphics/screen.cpp \
src/utils/graphics/textbox.cpp \
src/utils/helpers.cpp \
src/utils/graphics/button.cpp \
src/utils/graphics/menu.cpp \
src/utils/xml_parser/tag.cpp \
src/utils/xml_parser/document.cpp \
src/utils/xml_parser/xml_parser.cpp;
