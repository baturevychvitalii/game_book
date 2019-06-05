#include <math.h>
#include "game_state_manager.h"
#include "colors.h"
#include "game_exception.h"
#include "../utils/xml_parser/xml_parser.h"
#include "../utils/graphics/textbox.h"

#include "main_menu.h"
#include "pause_state.h"
#include "inventory_state.h"
#include "../game_book/page_types/story.h"
#include "../game_book/page_types/trade.h"

size_t  menu_state = 0,
        pause_state = 1,
        game_state = 2,
	//  imagine game state 3 here
		inventory_state = 4;

GameStateManager::GameStateManager()
    : current_state(0), shall_run(true), player(nullptr)
{
    InitColors();

    // create states
    states[menu_state] = std::move(std::make_unique<MainMenu>(this));
    states[pause_state] = std::move(std::make_unique<PauseState>(this));
    states[game_state] = std::move(std::make_unique<Page>(this));
	states[inventory_state] = std::move(std::make_unique<InventoryState>(this));
	

    // add cross available helper screens
	// controls
    {
        auto & text = wm.AddScreen("controls").
                      AddWindow<graphics::Textbox>(
            "controls info",
            graphics::max_x,
            0,
            0,
            controls_color
        );
        text.AppendText("Controls");
        text.AppendText("press any key to continue");
        text.NewLine();
        text.NewLine("   ^ v      switch button (menu)");
		text.NewLine("pgup pgdown scroll window  (all)");
        text.NewLine("   j k      scroll window  (all)");
        text.NewLine("  Enter     select          all)");
        text.NewLine("    p       pause         (game)");
        text.NewLine("    i       inventory     (game)");
		text.NewLine("    n       switch menu  (trade)");
		text.Commit();
		text.SetHeight(graphics::max_y);
    }

	// about
    {
        auto & text = wm.AddScreen("about").
        AddWindow<graphics::Textbox>(
            "about info",
            graphics::XPercent(77),
            graphics::YPercent(50),
            graphics::XPercent(33) / 2,
            about_color
        ).
        AppendText("By Vitalii Baturevych").
		AppendText("color theme by Olga Zavatskaya");
		text.Commit();
		text.ProlongueToBottom();		
    }

	// no money
	{
        auto & text = wm.AddScreen("no money").
                      AddWindow<graphics::Textbox>(
            "no money info",
            graphics::max_x,
            0,
            0,
            no_money_color
        ).
        AppendText("not enough green");
		text.NewLine();
		std::string line;
		for (size_t i = 0; i < graphics::YPercent(33); i++)
		{
			if (i % 2)
				line = " $";
			else
				line = "$ ";

			for (int a = 1; a < static_cast<int>(std::log2(graphics::XPercent(77))); a++)
			{
				line += line;
			}
			text.NewLine(line);
		}
		text.Commit();
		text.SetHeight(graphics::max_y);	
	}

	// exception
	{    
		wm.AddScreen("exception").
		AddWindow<graphics::Textbox>(
			"err",
			graphics::XPercent(80),
			graphics::YPercent(10),
			graphics::XPercent(10),
			error_color
		);
	}
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::SwitchState(size_t state_code, Notify notification)
{
    current_state = state_code;
    states[current_state]->GetNotification(notification);
}

void GameStateManager::SendNotification(size_t state_code, Notify notification)
{
	states[state_code]->GetNotification(notification);
}

void GameStateManager::Launch()
{
    states[current_state]->Draw();
    int input;
    while (shall_run)
    {
        do
            input = getch();
        while (!states[current_state]->Reacted(input));
        
        states[current_state]->Draw();
    }  
}

void GameStateManager::Stop()
{
    shall_run = false;
}

void GameStateManager::PopUp(const std::string & screen)
{
    wm.SelectScreen(screen);
    wm.Draw();
    getch();
}

void GameStateManager::DisplayException(const std::exception & e){
    auto & err = wm.SelectScreen("exception").
    GetWindow<graphics::Textbox>("err");
    err.Clear();
    err.AppendText("exception was thrown");
    err.AppendText(e.what());
    PopUp("exception");
}

void GameStateManager::TurnPage(const std::string & filename)
{
    auto doc = xml::Parser::GetDoc(filename);
    auto root = doc.Root();
    if (root.Name() != "page")
        throw GameException("root tag of a file must be <page type=\"page_tyepe\">");

    std::string type = root.Prop("type");

    game_state = game_state == 2 ? 3 : 2;
    current_state = game_state;
    if (type == "story")
        states[game_state].reset(new Story(root, this));
	else if (type == "trade")
		states[game_state].reset(new game_states::Trade(root, this));
    else
        throw GameException("file is not in correct format. Page must have a type");

}
