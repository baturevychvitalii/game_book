#ifndef __GRAPHICS_WINDOW__
#define __GRAPHICS_WINDOW__

#include <ncurses.h>
#include <stdexcept>
#include "graphics_exception.h"
#include "../interfaces/IChangeable.h"

namespace graphics
{
    class Window : public IChangeable
    {
        protected:
            size_t act_h, act_w, on_screen_h, on_screen_w;
            short act_y, act_x, on_screen_y, on_screen_x;

            short window_color;

            short MidXStart(short len) const;
            short MidYStart(short len) const;

            void UpdateOnScreenWidth() noexcept;
            void UpdateOnScreenHeight() noexcept;
            void UpdateOnScreenPositin() noexcept;
        public:
            static short max_y, max_x;
            static void SetMaxes(short maxy, short maxx) noexcept;
            static size_t XPercent(size_t percents) noexcept;
            static size_t YPercent(size_t percents) noexcept;

            Window(IChangeable * parent, size_t width, short y, short x, short color);
            Window(const Window & other) = delete;
            Window & operator=(const Window & other) = delete;
            virtual ~Window() = default;
            
            virtual size_t MinHeight() const = 0;
            void SetHeight(size_t new_height);
            

            short HighestPoint() const;
            short LowestPoint() const;
            short RightPoint() const;
            short LeftPoint() const;
            size_t Height() const;
            size_t Width() const;
            size_t ActualSpace() const;


            virtual void Move(short dy, short dx);
            void MoveTo(short y, short x);
            virtual void Draw();
    };
}

#endif
