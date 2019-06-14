#ifndef __GRAPHICS_MIRROR__
#define __GRAPHICS_MIRROR__

#include "window.h"

namespace graphics
{
	template <class Win = Window>
	class Mirror : public Window
	{
		Win & ref_window;

		void ApplyChange() override
		{
			ref_window.Commit();
			SetHeight(ref_window.Height());
		}

		void DrawSpecific() override
		{
			short mem_y = ref_window.HighestPoint(),
				  mem_x = ref_window.LeftPoint();
			ref_window.MoveTo(act_y, act_x);
			ref_window.Draw();
			ref_window.MoveTo(mem_y, mem_x);
		}

		public:
			Mirror(
				IChangeable * parent,
				size_t aka_width_but_wont_be_used,
				short y,
				short x,
				Win & window
			)
				: Window(parent, window.Width(), y, x, window.GetColor()),
				ref_window(window)
			{
				ref_window.AddDependent(this);
			}

			~Mirror()
			{
				ref_window.RemoveDependent(this);
			}

			size_t MinHeight() const override
			{
				return ref_window.MinHeight();
			}

			Win & operator ->()
			{
				return ref_window;
			}
	};
}

#endif

