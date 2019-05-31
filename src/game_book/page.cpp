#include "page.h"
#include "../game_handler/game.h"
#include "../game_handler/game_state_manager.h"
#include "../utils/graphics/menu.h"
#include "../game_handler/colors.h"

Page::Page(const xml::Tag & root, Game * g)
    : game(g), filename(root.GetFilename())
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
    game->SetTopAndBottom(head, cross);
}

xml::Tag Page::Serialize() const
{
    return xml::Tag("page").AddText(filename);
}

bool Page::Reacted(int input)
{
    graphics::Menu * cross = static_cast<graphics::Menu *>(&game->BotWindow());
    switch (input)
    {
        case KEY_UP:
            if (cross->ChoicesAreVisible())
                (*cross)--;
            break;
        case KEY_DOWN:
            if (cross->ChoicesAreVisible())
                (*cross)++;
            break;
        case 10: // Return pressed
            if (cross->ChoicesAreVisible())
            {
                // if this is last page -> go to main menu
                if (crossroads.empty())
                    game->gsm->SwitchState(menu_state);
                // else turn to next page
                else
                    game->TurnTo(crossroads[cross->GetChoice()].first);                
            }
            break;
        default:
            return false;
    }

    return true;
}
