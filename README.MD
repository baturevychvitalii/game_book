using ncurses library (https://invisible-island.net/ncurses/)
using libxml2 library (http://www.xmlsoft.org/)

This application is a demo of my programming skills)) and graphics library. 
Library is based on ncurses |-> targeted for linux.

finally added a makefile.

TODO:
allow binding relations between windows. for example window X is in
relation with window Y so X's top line is always N rows below Y's bottom
line. So when Y's height is changed X remains N rows below Y.

don't write characters which are off screen. Now if on screen space of the window > 0
it'll still process whole window.

do inputbox class: a window which will get user input in form of text from keyboard.

possibly keylistener is needed.

possibly the base of the window will becume ncurses pad. (created with newpad()). didn't test that, it might be a better way of doing things, cause it refreshes only part of the window. and sometimes there'll be no need in clearing whole screen with clear().
https://www.mkssoftware.com/docs/man3/curs_pad.3.asp
