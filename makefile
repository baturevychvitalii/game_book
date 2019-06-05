CXX=g++
CPPFILES=$(shell find src -name '*.cpp')
OBJFILES=$(patsubst src/%.cpp,obj/%.o,$(CPPFILES))
FLAGS=-g -Wall -pedantic -std=c++14 -l ncurses $(shell xml2-config --cflags) -l xml2



obj/%.o: src/%.cpp
	mkdir -p "$(@D)"
	$(CXX) $(FLAGS) -c $< -o $@

objects: $(OBJFILES)

executable: objects
	$(CXX) -o $@ $(FLAGS) $(OBJFILES)

clean:
	rm -r obj

rebuild: clean executable

run: executable
	./executable

memcheck: executable
	valgrind --leak-check=full ./executable
