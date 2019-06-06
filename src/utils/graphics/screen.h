#ifndef __GRAPHICS_SCREEN__
#define __GRAPHICS_SCREEN__

#include <memory>
#include <vector>
#include <map>

#include "window.h"

namespace graphics
{
	/**
	container of windows
	*/
    class Screen
    {
        std::map<std::string, std::unique_ptr<Window>> windows;
        public:
            const std::string Name;

            Screen(std::string name);
            Screen() = delete;
            Screen(const Screen & sc) = delete;
            Screen & operator=(const Screen & sc) = delete;
            ~Screen() = default;



            Screen & RemoveWindow(const std::string & id);
			Window & ReleaseWindow(const std::string & id);
            Screen & Clear();
            bool Empty() const;
            bool HasWindow(const std::string & id);
            Screen & Commit();
            void Draw();
            Screen & Move(short dy, short dx);
            Screen & Move(graphics::Direction direction, unsigned multiplier);
			Window & AddWindow(const std::string & id, Window & new_win);

            template <typename Win, typename ... UniqueArgs>
            Win & AddWindow(const std::string & id, size_t width, short y, short x, short bg_color, UniqueArgs && ... args)
            {
                if (HasWindow(id))
                    throw GraphicsException("window already exists");

                Win * new_win = new Win(nullptr, width, y, x, bg_color, std::forward<UniqueArgs>(args) ...);
                windows.emplace(id, new_win);
                return *new_win;
            }

            template <typename Win>
            Win & GetWindow(const std::string & id)
            {
                Win * result = dynamic_cast<Win *>(& GetWindow(id));
                if (!result)
                    throw GraphicsException("GetWindow called with invalid type.");

                return *result;
            }

            Window & GetWindow(const std::string & id);
    };
}

#endif
