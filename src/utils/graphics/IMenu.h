#ifndef __GRAPHICS_INTERFACE_MENU__
#define __GRAPHICS_INTERFACE_MENU__

#include <stdlib.h>
#include "button.h"

namespace graphics
{
	class IMenu : public Textbox
	{
		public:
			virtual bool NextIsVisible() const = 0;
			virtual bool PrevIsVisible() const = 0;
			virtual bool CurrIsVisible() const = 0;
			virtual size_t GetChoice() const = 0;
			virtual size_t Size() const = 0;
			virtual size_t Next() = 0;
			virtual size_t Prev() = 0;
	};
}


#endif
