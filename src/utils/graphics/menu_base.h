#ifndef __GRAPHICS_MENU_BASE__
#define __GRAPHICS_MENU_BASE__

#include <stdlib.h>
#include "button.h"

namespace graphics
{
	/**
	base of a menu.
	this class exists because i didn't want to mess with templates
	when passing menues as arguments
	*/
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
		virtual menu_base & NextSelect() = 0;
		virtual menu_base & PrevSelect() = 0;
		virtual menu_base & LowerSelect() = 0;
		virtual menu_base & UpperSelect() = 0;
		virtual menu_base & LeftSelect() = 0;
		virtual menu_base & RightSelect() = 0;

		virtual size_t GetChoice() const = 0;
		virtual Button & operator[](size_t idx) = 0;
		virtual bool Empty() const  = 0;
		virtual bool NextVisible() const = 0;
		virtual bool PrevVisible() const = 0;
		virtual bool CurrVisible() const = 0;
		virtual bool UpperVisible() const = 0;
		virtual bool LowerVisible() const = 0;
		virtual bool LeftVisible() const = 0;
		virtual bool RightVisible() const = 0;
	};
	
}

#endif
