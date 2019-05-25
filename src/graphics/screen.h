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

        Textbox & AddTextbox(size_t width, short y, short x, short color); 
        Menu & AddMenu(size_t width, short y, short x,
                       short bg_color,
                       short active_color,
                       short inactive_color,
                       size_t colomns);
        
        template <typename Win>
        Group<Win> & AddGroup(size_t width, short y, short x, short color,
                              size_t colomns, size_t y_indent, size_t x_indent)
        {
            Group<Win> * gr = new Group<Win>(nullptr, width, y, x, color, colomns, y_indent, x_indent);
            windows.emplace_back(gr);
            return *gr;
        }

        void RemoveWindow(Window & win);
        void Clear();
        void Commit();
        void Draw();
        void Move(short dy, short dx);
};


#endif
