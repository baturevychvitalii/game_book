#include "page_state.h"
#include "../game_handler/game_state_manager.h"
#include "../utils/graphics/menu.h"
#include "../game_handler/colors.h"
#include "../utils/xml_parser/xml_parser.h"

Page::Page(GameStateManager * gsm)
    : IGameState(gsm)
{
    // no this will wait for notification
}

Page::Page(const xml::Tag & root, GameStateManager * g)
    : IGameState(g), filename(root.GetFilename())
{
    crossroads.reserve(5);
    for (const xml::Tag & tag : root.Child("crossroad").GetVector("path"))
    {
        crossroads.emplace_back(tag.Prop("to"), tag.Text());
    }

    auto & head = AddWindow<graphics::Textbox>(
        "header",
        graphics::XPercent(100),
        0,
        0,
        page_header_color
    );
    head.AppendText(root.Child("header").Text());

    auto & cross = AddWindow<graphics::Menu>(
        "crossroads",
        graphics::max_x,
        0,
        0,
        page_crossroad_bg_color,
        page_crossroad_active_color,
        page_crossroad_inactive_color,
        2
    );

    if (crossroads.empty())
    {
        cross.AppendText("Finito");
        cross.NewLine();
        cross.AppendText("press 'Enter to quit to main menu'");
    }
    else
    {
        cross.AppendText("Where now, Lorry?");
        for (auto & pair : crossroads)
            cross.AddOption(pair.second);
    }
    
    SetTopAndBottom(head, cross);
    Commit();
}

void Page::GetNotification(Notify notification)
{
    switch (notification)
    {
        case Notify::Save:
            try
            {
                Save();
            }
            catch(const std::exception& e)
            {
                gsm->DisplayException(e);
                gsm->SwitchState(pause_state);            
            }
            break;
        case Notify::Load:
            try
            {
                Load();
            }
            catch(const std::exception& e)
            {
                gsm->DisplayException(e);
                gsm->SwitchState(menu_state);
            }
            break;
        case Notify::New:
            gsm->player.reset(new Creature());
            gsm->TurnPage(std::string("book/begin.xml"));
            break;
        case Notify::Continue:
            break;
        default:
            throw std::invalid_argument("game got wrong notification");
    }
}

void Page::Save() const
{
    auto root = xml::Tag("save");
    root.AddChild(Serialize());
    root.AddChild(gsm->player->Serialize());
    auto doc = xml::Parser::NewDoc("save.xml", root);
    doc.Save();
}

void Page::Load()
{
    auto doc = xml::Parser::GetDoc("save.xml");
    gsm->player.reset(new Creature(doc.Root().Child("player")));
    gsm->TurnPage(doc.Root().Child("page").Text());
}

xml::Tag Page::Serialize() const
{
    return xml::Tag("page").AddText(filename);
}

void Page::StandardManuHandlerProcess(graphics::Menu * crossroads_menu)
{
    // works only with crossroads menu
    if (crossroads_menu != BotWindow())
        throw std::invalid_argument("given menu, which should have been handled on the upper level");
    
    gsm->TurnPage(crossroads[crossroads_menu->GetChoice()].first);
}

bool Page::Reacted(int input)
{
    graphics::Menu * cross = static_cast<graphics::Menu *>(BotWindow());

    // if this is a last page
    if (crossroads.empty())
    {
        if (cross->IsVisible() && input == K_ENTER)
        {
            gsm->SwitchState(menu_state);
            return true;
        }
    }
    else if (StandardMenuHandlerReacted(cross, input))
        return true;

    if (input == 'p')
    {
        gsm->SwitchState(pause_state);
        return true;
    }
    
    return IGameState::Reacted(input);
}
