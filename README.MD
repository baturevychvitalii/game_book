
0 CONTENTS:
	1 Description
	2 Installation
		2.1 Dependencies
		2.2 Installation

1 DESCRIPTION
	This application is my university project in C++ (C++14). The goal of the project was to
	make a gamebook engine in C++.

	This programm is basically a interactive book reader. You feed an executable file
	(in our case ./demonstrator) with a book you want to read (in our case ./examples/)
	and enjoy. The book itself is a folder of XML files. Each XML file is a page of the
	book. If current page contains a story - XML file will have some header, and some text,
	about adventures of our hero. If a page is a fight - XML contains stats of a villain and
	description of his inventory. Each page (last is exception) has a set of choices where
	would you like to go next. By choosing - you follow to the next page, and so on, untill
	your hero gets killed, or the book is finished.

	The point was to create stories in a really fast way. The ./examples/ story itself
	was written in about 5 minutes. No coding is needed, Just write couple XMLs and
	interlink them between each other as in the example.

	I've put more effort and time into wrapping ncurses with C++ object features and levels
	of abstraction, so the class hierarchy of graphics part (see src/graphics) looks more
	or less the way I wanted it to look like.
	Graphics part provided me with high level interface to several types of windows,
	which made it possible to say: "hey, create menu at X,Y, it'll be white with pink buttons,
	and choices will be A,B,C". This would create menu, give me handlers to move it around the
	screen, wouldn't draw the part, which is off screen, provide me with handlers to move around
	menu selections and many more things.


2 INSTALLATION
	1). Dependencies:
		ncurses library (https://invisible-island.net/ncurses/)
		libxml2 library (http://www.xmlsoft.org/)
		libxml2 and ncurses libraries are usually preinstalled on major linux distributions so no worries.
		C++ compiler, with support of c++14 (I used gcc)
		Cmake

	2). Installation:
		(following things must be fired in linux terminal, if you're on Windows use Cygwin or WSL)
		-Create makefile with
			$ cmake CMakeLists.txt
		-Build binary
			$ make demonstrator
		-Read examples book using compiled demonstrator
			$ ./demonstrator examples

