using ncurses library (https://invisible-island.net/ncurses/)

make temporary_build.sh executable and execute it.
or simply copy paste it's contents into terminal.
later will switch to Make.

If you decide to make normal Makefile - don't use CMake. I'm using this project
at university, and we are allowed to use only pure make.

src/main.cpp now is an example of application of src/graphics/* library
I'll open this project when i pass my semestral work (9.6.2019)

TODO:
allow binding relations between windows. for example window X is in
relation with window Y so X's top line is always N rows below Y's bottom
line. So when Y's height is changed X remains N rows below Y.

don't write characters which are off screen. Now if on screen space of the window > 0
it'll still process whole window.

do inputbox class: a window which will get user input in form of text from keyboard.

possibly keylistener is needed.
