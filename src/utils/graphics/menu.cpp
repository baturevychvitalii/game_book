#include "menu.h"
#include "../helpers.h"

graphics::Menu::Menu(IChangeable * parent, size_t width, short y, short x,
           short bg_color,
           short active_color,
           short inactive_color,
           size_t colomns)
    : Textbox(parent, width, y, x, bg_color),
      buttons(this, width - 2, 0, 0, bg_color, colomns, 1, 2),
      current(0),
      active_c(active_color),
      inactive_c(inactive_color)
{
}

size_t graphics::Menu::MinHeight() const
{
    return Textbox::MinHeight() + buttons.Height() + 1;
}

void graphics::Menu::Draw()
{
    Textbox::Draw();
    buttons.Draw();
}

void graphics::Menu::MoveChildren(short dy, short dx)
{
    buttons.Move(dy,dx);
}

size_t graphics::Menu::TopIndent() const
{
    return 1;
}

int graphics::Menu::FindButton(const std::string & text) const
{
    for (size_t i = 0; i < buttons.Size(); i++)
    {
        if (buttons[i].GetText().compare(text) == 0)
            return i;
    }

    return -1;
}

void graphics::Menu::ApplyChange()
{
    buttons.Commit();
    buttons.MoveTo(act_y + Textbox::MinHeight(), act_x + 1);
    
    if (act_h < MinHeight())
        SetHeight(Textbox::MinHeight() + buttons.MinHeight() + 1);
}

size_t graphics::Menu::AddOption(const std::string & text)
{
    if (FindButton(text) != -1)
        throw std::invalid_argument("requested option already exists");

    buttons.EmplaceBack(active_c, inactive_c).AppendText(text);
    buttons[current].Select();
    return buttons.Size() - 1;
}

size_t graphics::Menu::RemoveOption(const std::string & to_remove)
{
    int idx = FindButton(to_remove);
    if (idx == -1)
        throw std::invalid_argument("trying to remove unexisting button");
    
    buttons.Erase(idx);
    return idx;
}

size_t graphics::Menu::operator++(int)
{
    if (current != buttons.Size() - 1)
    {
        buttons[current++].Unselect();
        buttons[current].Select();
    }

    return current;
}

size_t graphics::Menu::operator--(int)
{
    if (current != 0)
    {
        buttons[current--].Unselect();
        buttons[current].Select();
    }

    return current;
}

size_t graphics::Menu::GetChoice() const
{
    return current;
}

std::string graphics::Menu::GetChoiceText() const
{
    return std::move(buttons[current].GetText());
}

bool graphics::Menu::ChoicesAreVisible() const
{
    if (buttons.Size() > 0)
    {
        if (!buttons[current].IsVisible())
            return false;
        if (current > 0 && !buttons[current - 1].IsVisible())
            return false;
        if (current < buttons.Size() - 1 && !buttons[current + 1].IsVisible())
            return false;
        
        return true;
    }
    else
    {
        return IsVisible();
    }    
}

