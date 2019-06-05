#ifndef __GRAPHICS_GROUP__
#define __GRAPHICS_GROUP__
#include <vector>
#include <memory>
#include "window.h"
#include "../helpers.h"


namespace graphics
{
    template <class Win>
    class Group : public Window
    {
        size_t colomns, window_width, y_indent, x_indent, minimal_h;
        std::vector<std::unique_ptr<Win>> windows;
		bool draw_background;

        void ApplyChange() override
        {
            if (windows.empty())
            {
                act_h = 0;
                UpdateOnScreenHeight();
                return;
            }

            size_t in_last_row = windows.size() % colomns;
            size_t normal_rows = (windows.size() - in_last_row) / colomns;
            
            // get biggest height
            size_t window_height = 0;
            for (const auto & win : windows)
            {
                // possibly some windows in group were changed
                // first apply changes to them so we know their up to date scales
                win->Commit();

                if (win->Width() > window_width)
                    throw GraphicsException("window is too wide to fit in this column set");
                if (win->Height() > window_height)
                    window_height = win->Height();
            }

            // now we have maximum window height
            // make them all have same height and move them to correct positions
            short startx = act_x, starty = act_y;
            for (size_t r = 0; r < normal_rows; r++, starty += window_height + y_indent)
            {
                startx = act_x;
                for (size_t c = 0; c < colomns; c++, startx += window_width + x_indent)
                {
                    windows[r * colomns + c]->MoveTo(starty, startx);
                    windows[r * colomns + c]->SetHeight(window_height);
                }
            }

            startx = MidXStart(in_last_row * (window_width + x_indent) - x_indent);
            for(size_t c = windows.size() - in_last_row; c < windows.size(); c++, startx += window_width + x_indent)
            {
                windows[c]->MoveTo(starty, startx);
                windows[c]->SetHeight(window_height);
            }

            minimal_h = Distance(windows[0]->HighestPoint(), windows[windows.size() - 1]->LowestPoint());
            if (act_h < minimal_h)
            {
                act_h = minimal_h;
                UpdateOnScreenHeight();
            }
        }

        void MoveChildren(short dy, short dx) override
        {
            for (auto & window : windows)
                window->Move(dy, dx);
        }
		
		void DrawSpecific() const override
		{
			if (draw_background)
				DrawBackground();

			for (auto & window : windows)
				window->Draw();
		}

        public:
            Group(IChangeable * parent, size_t width, short y, short x, short color, size_t colomns, size_t y_indent, size_t x_indent)
                : Window(parent, width, y, x, color),
                colomns(colomns),
                window_width((act_w + x_indent) / colomns - x_indent),
                y_indent(y_indent),
                x_indent(x_indent),
				draw_background(false)
            {
                if (colomns == 0)
                    throw GraphicsException("colomns must be > 0");

                windows.reserve(10);
            }

            Group(const Group & gr) = delete;
            Group & operator=(const Group & gr) = delete;

            size_t MinHeight() const override
            {
                if (!UpToDate())
                    throw GraphicsException("minimal height of the group is determined during commit");
                
                return minimal_h;
            }

			Group & SetDrawBackground(bool value = true)
			{
				draw_background = value;
				return *this;
			}

			// Allows to add derived classes to group
            template<typename Window_type = Win, typename ... ConsturctorParams>
            Window_type & Emplace(size_t idx, ConsturctorParams && ... params)
            {
                if (idx > windows.size())
                    throw std::invalid_argument("idx");

                windows.emplace(windows.begin() + idx, new Window_type(this, window_width, 0, 0, std::forward<ConsturctorParams>(params) ...));
                NotifyChange();
                return static_cast<Window_type &>(*(windows[idx]));
            }

            template<typename Window_type = Win, typename ... Args>
            Window_type & EmplaceBack(Args && ... args)
            {
                return Emplace<Window_type>(windows.size(), std::forward<Args>(args) ...);
            }

            Win & Emplace(size_t idx, Win & new_win)
            {
                if (idx > windows.size())
                    throw std::invalid_argument("idx");
				
				if (new_win.HasParent())
					throw GraphicsException("item still has parent");

                new_win.SetParent(this);
                windows.emplace(windows.begin() + idx, &new_win);
				NotifyChange();
                return *(windows[idx]);
            }

            Win & EmplaceBack(Win & new_win)
            {
                return Emplace(windows.size(), new_win);
            }

            Group & Erase(size_t idx)
            {
                if (idx >= windows.size())
                    throw std::invalid_argument("trying to erase window, which doesn't exist");

                windows.erase(windows.begin() + idx);
                NotifyChange();
                return *this;
            }

            Win & Release(size_t idx)
            {
                if (idx >= windows.size())
                    throw std::invalid_argument("trying to erase window, which doesn't exist");
                
				auto * to_release = windows[idx].release();
                to_release->SetParent(nullptr);
				Erase(idx);
                return *to_release;
            }

            Win & operator[] (size_t idx)
            {
                if (idx >= windows.size() || idx < 0)
                    throw std::invalid_argument("trying to access window, which doesn't exist");

                return *(windows[idx]);
            }

            const Win & operator[] (size_t idx) const
            {
                if (idx >= windows.size() || idx < 0)
                    throw std::invalid_argument("trying to access window, which doesn't exist");

                return *(windows[idx]);
            }

            size_t Size() const
            {
                return windows.size();
            }

            bool Empty() const
            {
                return windows.empty();
            }
    };
}

#endif
