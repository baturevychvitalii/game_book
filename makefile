CXX=g++
CPPFILES=$(shell find src -name '*.cpp')
OBJFILES=$(patsubst src/%.cpp,obj/%.o,$(CPPFILES))
FLAGS=-g -Wall -pedantic -l ncurses $(shell xml2-config --cflags) -l xml2



executable: all

all: $(OBJFILES)

obj/%.o: src/%.cpp
	mkdir -p "$(@D)"
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -r obj
