#include "page.h"
#include "../game_handler/game.h"
#include "../utils/graphics/menu.h"
#include "../game_handler/colors.h"

Page::Page(const xml::Tag & root, Game * g)
    : game(g)
{
    crossroads.reserve(5);
    for (const xml::Tag & tag : root.Child("crossroad").GetVector("path"))
    {
        crossroads.emplace_back(tag.Prop("to"), tag.Text());
    }

    game->Clear();
    auto & head = game->AddWindow<graphics::Textbox>(
        "header",
        graphics::XPercent(100),
        0,
        0,
        page_header_color
    );
    head.AppendText(root.Child("header").Text()).
    Commit();
    top = &head;

    auto & cross = game->AddWindow<graphics::Menu>(
        "crossroads",
        graphics::XPercent(90),
        0,
        graphics::XPercent(5),
        page_crossroad_bg_color,
        page_crossroad_active_color,
        page_crossroad_inactive_color
    );

    if (crossroads.empty())
        cross.AppendText("Finito");
    else
    {
        cross.AppendText("Where now, Lorry?");
        for (auto & pair : crossroads)
            cross.AddOption(pair.second);
    }
    
    cross.Commit();
    bot = &cross;
}

graphics::Window & Page::

std::string Page::GetNextPage() const
{
    if (crossroads.empty())
        throw "shouldn't have come to this point, Play() should have returned 1";
        
    auto & screen = wm.SelectScreen("crossroad");
    auto & menu = screen.AddWindow<graphics::Menu>(
        "menu",
        graphics::XPercent(90),
        0,
        graphics::XPercent(5),
        magneta_on_black,
        hacker,
        cyan_on_black,
        2
    );
    menu.AppendText("Where now, Lorry?");
    for (auto & pair: crossroads)
        menu.AddOption(pair.second);

    size_t choice = GetMenuSelection(menu);
    screen.Clear();
    return crossroads[choice].first;
}

xml::Tag Page::Serialize() const
{
    return xml::Tag("page").AddText(filename);
}
