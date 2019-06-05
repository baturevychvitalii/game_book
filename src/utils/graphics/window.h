#ifndef __GRAPHICS_WINDOW__
#define __GRAPHICS_WINDOW__

#include <ncurses.h>
#include <stdexcept>
#include "graphics_exception.h"
#include "IChangeable.h"

namespace graphics
{
    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    extern size_t max_x, max_y;

    size_t XPercent(size_t percents) noexcept;
    size_t YPercent(size_t percents) noexcept;

    void CastDirection(Direction direction, unsigned multiplier, short & dy, short & dx);

    class Window : public IChangeable
    {
        bool sticky;
        virtual void MoveChildren(short dy, short dx)
        {
        }

		virtual void DrawSpecific() const = 0;

        protected:
            size_t act_h, act_w, on_screen_h, on_screen_w;
            short act_y, act_x, on_screen_y, on_screen_x;

            size_t OnScreenSpace() const;

            short window_color;

            short MidXStart(short len) const;
            short MidYStart(short len) const;

            void UpdateOnScreenWidth() noexcept;
            void UpdateOnScreenHeight() noexcept;
            void UpdateOnScreenPositin() noexcept;
            void DrawBackground() const;
        public:
            Window(IChangeable * parent, size_t width, short y, short x, short color);
            Window(const Window & other) = delete;
            Window & operator=(const Window & other) = delete;
            virtual ~Window() = default;
            
            virtual size_t MinHeight() const = 0;
            Window & SetHeight(size_t new_height);
			Window & ProlongueToBottom();
            Window & SetColor(short new_color);
            Window & SetSticky(bool value = true);

            short HighestPoint() const;
            short LowestPoint() const;
            short RightPoint() const;
            short LeftPoint() const;
            size_t Height() const;
            size_t Width() const;
            size_t ActualSpace() const;
            size_t VisiblePercent() const;

            static size_t visible_consiederation;
            bool IsVisible() const;

            Window & Move(Direction direction, unsigned multiplier = 1);
            Window & Move(short dy, short dx);
            Window & MoveTo(short y, short x);
			Window & MoveToTouch(Direction direction);
            void Draw() const;
    };
}

#endif
