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

	/*
	 * terminal maximum colomns and rows
	 */
	extern size_t max_x, max_y;

	/*
	 * @param percents of maximum screen width
	 * @return width of the element the way it is X percents of max_x
	 */
	size_t XPercent(size_t percents) noexcept;

	/*
	 * @return height of the element the way it is X percents of max_y
	 */
	size_t YPercent(size_t percents) noexcept;

	/*
	 * casts direction direction and multiplier to movement vector
	 */
	void CastDirection(Direction direction, unsigned multiplier, short & dy, short & dx); 
	/*
	 * base of all drawable objects
	 */
	class Window : public IChangeable
	{
		bool sticky;
		virtual void MoveChildren(short dy, short dx)
		{
		}

		virtual void DrawSpecific() = 0;

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

			/*
			 * if window is not touching bottom of the screen -> increase it's height to do so
			 */
			Window & ProlongueToBottom();
			Window & SetColor(short new_color);
			short GetColor() const;

			/*
			 * makes window ignore movement
			 */
			Window & SetSticky(bool value = true);

			short HighestPoint() const;
			short LowestPoint() const;
			short RightPoint() const;
			short LeftPoint() const;
			size_t Height() const;
			size_t Width() const;
			size_t ActualSpace() const;
			size_t VisiblePercent() const;

			/*
			 * percent value, after which window is considered visible
			 */
			static size_t visible_consiederation;
			bool Visible() const;

			Window & Move(Direction direction, unsigned multiplier = 1);
			Window & Move(short dy, short dx);
			Window & MoveTo(short y, short x);

			/*
			 * Move window to touch a wall of the screen
			 */
			Window & MoveToTouch(Direction direction);

			/*
			 * Draws window to screen
			 */
			void Draw();
	};
}

#endif
