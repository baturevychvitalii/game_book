#include "textbox.h"
#include "../utils/helpers.h"

Textbox::Textbox(IChangeable * parent, size_t width, short y, short x, short color)
    : Window(parent, width, y, x, color)
{
}

void Textbox::ApplyChange()
{
    if (act_h < MinHeight())
        SetHeight(MinHeight());
}

void Textbox::Draw()
{
    Window::Draw();

    short starty = act_y + TopIndent();
    short startx;
    for (const auto & pair : lines)
    {
        startx = MidXStart(pair.first.length());
        attron(COLOR_PAIR(pair.second));
        
        for (size_t i = 0; i < pair.first.length(); i ++)
            mvaddch(starty, startx + i, pair.first[i]);

        attroff(COLOR_PAIR(pair.second));
        starty++;
    }
}

size_t Textbox::TopIndent() const
{
    return MidYStart(lines.size()) - act_y;
}

size_t Textbox::MinHeight() const
{
    return lines.size() + 2;
}

size_t Textbox::SizeLines() const
{
    return lines.size();
}

void Textbox::InsertText(size_t idx, const std::string & text, short color)
{
    if (idx > lines.size())
        throw std::invalid_argument("idx");
    
    
    std::vector<std::string> broken_into_lines(BreakIntoLines(text, act_w - 2));

    for (size_t i = 0; i < broken_into_lines.size(); i++)
    {
        lines.emplace(lines.begin() + idx + i, broken_into_lines[i], color == -1 ? window_color : color);
    }

    NotifyChange();
}

void Textbox::AppendText(const std::string & text, short color)
{
    InsertText(lines.size(), text, color);
}

void Textbox::NewLine()
{
    lines.emplace_back("", window_color);

    NotifyChange();
}

void Textbox::EraseLines(size_t idx, size_t n)
{
    if (idx >= lines.size())
        throw std::invalid_argument("idx");
    
    lines.erase(lines.begin() + idx, lines.begin() + idx + n);
    NotifyChange();
}

void Textbox::AlterText(size_t idx, const std::string & new_text)
{
    if (idx >= lines.size())
        throw std::invalid_argument("idx");

    if (new_text.length() > act_w - 2)
        throw std::invalid_argument("new_text");

    lines[idx].first = new_text;
}

void Textbox::AlterColor(size_t idx, short color)
{
    lines[idx].second = color;
}

const std::string & Textbox::LineAt(size_t idx) const
{
    return lines[idx].first;
}

std::string Textbox::GetText(char delim_lines) const
{
    if (lines.empty())
        return "";

    std::string all_text = lines[0].first;
    for (size_t i = 1; i < lines.size(); i++)
        all_text += delim_lines + lines[i].first;

    return all_text;    
}