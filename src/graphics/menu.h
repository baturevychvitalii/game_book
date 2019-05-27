#ifndef __GRAPHICS_MENU__
#define __GRAPHICS_MENU__

#include <memory>
#include "button.h"
#include "group.h"

namespace graphics
{
    class Menu final : public Textbox
    {
        Group<Button> buttons;
        size_t current;
        short active_c, inactive_c;

        int FindButton(const std::string & text) const;

        void ApplyChange() override;
        size_t TopIndent() const override;
        public:
            Menu(IChangeable * parent,
                size_t width,
                short y,
                short x,
                short bg_color,
                short active_color,
                short inactive_color,
                size_t colomns);
            Menu(const Menu & menu) = delete;
            Menu & operator=(const Menu & menu) = delete;

            void Move(short dy, short dx) override;
            size_t MinHeight() const override;
            void Draw() override;

            void AddOption(const std::string & new_option);
            void RemoveOption(const std::string & to_remove);

            size_t operator++(int);
            size_t operator--(int);
            size_t GetChoice() const;
            std::string GetChoiceText() const;
    };
}

#endif
