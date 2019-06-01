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
        void MoveChildren(short dy, short dx) override;
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

            size_t MinHeight() const override;
            void Draw() override;

            size_t AddOption(const std::string & new_option);
            size_t RemoveOption(const std::string & to_remove);
            size_t OptionsSize() const;

            size_t operator++();
            size_t Next();
            size_t operator--();
            size_t Prev();
            size_t GetChoice() const;
            std::string GetChoiceText() const;
            bool ChoicesAreVisible() const;
            bool NextIsVisible() const;
            bool PrevIsVisible() const;
            bool CurrIsVisible() const;
    };
}

#endif
