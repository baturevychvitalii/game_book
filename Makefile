CXX=g++
CPPFILES=$(shell find src -name '*.cpp')
OBJFILES=$(patsubst src/%.cpp,obj/%.o,$(CPPFILES))
FLAGS=-g -Wall -pedantic -std=c++14 -l ncurses $(shell xml2-config --cflags) -l xml2
EXECUTABLE=baturvit



obj/%.o: src/%.cpp
	mkdir -p "$(@D)"
	$(CXX) $(FLAGS) -c $< -o $@

all: $(OBJFILES)

compile: all
	$(CXX) -o $(EXECUTABLE) $(FLAGS) $(OBJFILES)

clean:
	rm -r obj; rm $(EXECUTABLE); rm save.xml

run: all
	./$(EXECUTABLE)

memcheck: executable
	valgrind --leak-check=full ./$(EXECUTABLE)
