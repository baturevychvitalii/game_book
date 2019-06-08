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
    ).
    AppendText(root.Child("header").Text());

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
			try
			{
				gsm->player.reset(new Creature());
				gsm->TurnPage("begin.xml");
				gsm->SendNotification(inventory_state, Notify::New);
			}
			catch(const std::exception& e)
			{
				gsm->DisplayException(e);
				gsm->SwitchState(menu_state);
			}
			
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

static void RemoveFirstFolderName(std::string & filo)
{
	size_t found = filo.find('/');
	if (found == std::string::npos)
		throw std::invalid_argument("wrong save.xml format");
	
	filo.erase(filo.begin(), filo.begin() + found);
}

void Page::Load()
{
    auto doc = xml::Parser::GetDoc("save.xml");
    gsm->player.reset(new Creature(doc.Root().Child("player")));
	std::string now_will_be_page =doc.Root().Child("page").Text();
	RemoveFirstFolderName(now_will_be_page);
    gsm->TurnPage(now_will_be_page);
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
    else
	{
		try
		{    
			gsm->TurnPage(crossroads[crossroads_menu->GetChoice()].first);
		}
		catch (std::exception & e)
		{
			gsm->DisplayException(e);
		}
	}
}

bool Page::Reacted(int input)
{
	switch (input)
	{
		case 'p':
		case 'P':
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
