#ifndef __GRAPHICS_SCREEN__
#define __GRAPHICS_SCREEN__

#include <memory>
#include <vector>

#include "menu.h"

class Screen
{
    std::vector<std::unique_ptr<Window>> windows;
    public:
        Screen();
        Screen(const Screen & sc) = delete;
        Screen & operator=(const Screen & sc) = delete;
        ~Screen() = default;


        const Window & LastAdded() const;

        void RemoveWindow(Window & win);
        void Clear();
        void Commit();
        void Draw();
        void Move(short dy, short dx);

        template <typename Win, typename ... UniqueArgs>
        Win & AddWindow(size_t width, short y, short x, short bg_color, UniqueArgs && ... args)
        {
            Win * new_win = new Win(nullptr, width, y, x, bg_color, std::forward<UniqueArgs>(args) ...);
            windows.emplace_back(new_win);
            return *new_win;
        }
};


#endif
