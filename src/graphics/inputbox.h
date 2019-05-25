#ifndef __GRAPHICS_INPUTBOX__
#define __GRAPHICS_INPUTBOX__

#include "textbox.h"

class Inputbox : public Textbox
{

    public:
        Inputbox(IChangeable * parent, size_t width, short y, short x, short color);
        Inputbox(const Inputbox & other) = delete;
        Inputbox & operator=(const Inputbox & other) = delete;

        

};

#endif
