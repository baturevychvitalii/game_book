#ifndef __GRAPHICS_MENU_BASE__
#define __GRAPHICS_MENU_BASE__

#include <stdlib.h>
#include "textbox.h"

namespace graphics
{
	struct menu_base : Textbox
	{
		menu_base(
			IChangeable * parent, 
			size_t width,
			short y,
			short x,
			short bg_color
		)
			: Textbox(parent, width, y, x, bg_color)
		{
		}

		virtual size_t Size() const = 0;
		virtual size_t Next() = 0;
		virtual size_t Prev() = 0;
		virtual size_t GetChoice() const = 0;
		virtual bool Empty() const  = 0;
		virtual bool NextIsVisible() const = 0;
		virtual bool PrevIsVisible() const = 0;
		virtual bool CurrIsVisible() const = 0;
	};
	
}

#endif
