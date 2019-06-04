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

    auto & cross = AddWindow<graphics::Menu<>>(
        "crossroads",
        graphics::max_x,
        0,
        0,
        menu_bg_color,
        menu_active_color,
        menu_inactive_color,
        2
    );

    if (crossroads.empty())
    {
        cross.AppendText("Finito");
        cross.NewLine();
        cross.AppendText("use pause to quit");
    }
    else
    {
        cross.AppendText("Where now, Lorry?");
        for (auto & pair : crossroads)
            cross.AddOption().AppendText(pair.second);
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
				gsm->SendNotification(inventory_state, Notify::New);
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
			gsm->SendNotification(inventory_state, Notify::New);
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

void Page::ProcessMenuSelection(graphics::menu_base * crossroads_menu)
{
    // works only with crossroads menu
    if (crossroads_menu != BotWindow())
        throw std::invalid_argument("given menu, which should have been handled on the upper level");
    
    gsm->TurnPage(crossroads[crossroads_menu->GetChoice()].first);
}

bool Page::Reacted(int input)
{
    graphics::menu_base * cross = static_cast<graphics::menu_base *>(BotWindow());

	if (StandardMenuHandlerReacted(cross, input))
		return true;

	switch (input)
	{
		case 'p':
			gsm->SwitchState(pause_state);
			return true;
		case 'i':
		case 'I':
			gsm->SwitchState(inventory_state, Notify::Continue);
			return true;
		default:
			return IGameState::Reacted(input);
	}
}
