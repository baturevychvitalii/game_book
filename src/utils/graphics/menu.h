#ifndef __GRAPHICS_MENU__
#define __GRAPHICS_MENU__

#include <memory>
#include "group.h"
#include "menu_base.h"

namespace graphics
{
	template<class Butt>
    class Menu : public menu_base
    {
        Group<Butt> buttons;
        size_t current;
        short active_c, inactive_c;

        void ApplyChange() override
		{
			buttons.Commit();
			buttons.MoveTo(act_y + Textbox::MinHeight(), act_x + 1);
			
			if (act_h < MinHeight())
				SetHeight(Textbox::MinHeight() + buttons.MinHeight() + 1);
		}

        size_t TopIndent() const override
		{
			return 1;
		}

        void MoveChildren(short dy, short dx) override
		{
			buttons.Move(dy,dx);
		}


		void DrawSpecific() const override
		{
			Textbox::DrawSpecific();
			buttons.Draw();
		}
        public:
            Menu(IChangeable * parent,
                size_t width,
                short y,
                short x,
                short bg_color,
                short active_color,
                short inactive_color,
                size_t colomns)
				: menu_base(parent, width, y, x, bg_color),
				buttons(this, width - 2, 0, 0, bg_color, colomns, 1, 2),
				current(0),
				active_c(active_color),
				inactive_c(inactive_color)
			{
			}

            Menu(const Menu & menu) = delete;
            Menu & operator=(const Menu & menu) = delete;

            size_t MinHeight() const override
			{
				return Textbox::MinHeight() + buttons.Height() + 1;
			}

			template<typename Derived_butt = Butt, typename ... Args>
			Derived_butt & AddOption(Args && ... args)
			{
				Derived_butt & new_butt = buttons.template EmplaceBack<Derived_butt>(active_c, inactive_c, std::forward<Args>(args) ...);
				if (buttons.Size() == 1)
				{
					current = 0;
					buttons[current].Select();
				}

				return new_butt;
			}

			Butt & AddOption(Butt & button)
			{
				Butt & new_but = buttons.EmplaceBack(button);
				if (buttons.Size() == 1)
				{
					current = 0;
					buttons[current].Select();
				}

				return new_but;
			}

            Menu & EraseOption(size_t idx)
			{       
				buttons.Erase(idx);

				// if deleting currently selected element
				if (idx == current && !buttons.Empty())
				{
					current = 0;
					buttons[current].Select();
				}

				return *this;
			}

			Butt & ReleaseOption(size_t idx)
			{
				return buttons.Release(idx);
			}


			Butt & operator[](size_t idx)
			{
				return buttons[idx];
			}

			const Butt & operator[](size_t idx) const
			{
				return buttons[idx];
			}

            size_t Size() const
			{
				return buttons.Size();
			}

            size_t Next()
			{
				if (buttons.Empty())    
					throw GraphicsException("there are no buttons");
				

				if (current != buttons.Size() - 1)
				{
					buttons[current++].Unselect();
					buttons[current].Select();
				}

				return current;
			}

            size_t Prev()
			{
				if (buttons.Empty())    
					throw GraphicsException("there are no buttons");

				if (current != 0)
				{
					buttons[current--].Unselect();
					buttons[current].Select();
				}

				return current;
			}

			size_t GetChoice() const
			{
				if (buttons.Empty())
					throw GraphicsException("there are no buttons");
				
				return current;
			}

            bool Empty() const
			{
				return buttons.Empty();
			}

            bool NextIsVisible() const
			{
				if (buttons.Empty())
					throw GraphicsException("there are no choices");

				if (current < buttons.Size() - 1 && !buttons[current + 1].IsVisible())
					return false;

				return true;
			}

            bool PrevIsVisible() const
			{
				if (buttons.Empty())
					throw GraphicsException("there are no choices");

				if (current > 0 && !buttons[current - 1].IsVisible())
					return false;

				return true;
			}

            bool CurrIsVisible() const
			{
				if (buttons.Empty())
					throw GraphicsException("there are no choices");

				return buttons[current].IsVisible();
			}

			size_t WidthShallBe() const
			{
				return buttons.WidthShallBe();
			}
    };
}

#endif
