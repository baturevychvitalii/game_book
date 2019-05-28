#include "page.h"

Page::Page(const xml::Tag & t)
    : header(t.Child("header").Text())
{
    crossroads.reserve(5);
    for (const xml::Tag & tag : t.Child("crossroad").GetVector("path"))
    {
        crossroads.emplace_back(tag.Prop("to"), tag.Text());
    }
}

std::string Page::ShowCrossroad() const
{
    auto & screen = wm.SelectScreen("crossroad");
    auto & menu = screen.AddWindow<graphics::Menu>(
        graphics::Window::XPercent(90),
        0,
        graphics::Window::XPercent(5),
        magneta_on_black,
        hacker,
        cyan_on_black,
        2
    );
    menu.AppendText("Where now, Lorry?");
    for (auto & pair: crossroads)
        menu.AddOption(pair.second);

    return crossroads[GetMenuSelection(menu)].first;
}
