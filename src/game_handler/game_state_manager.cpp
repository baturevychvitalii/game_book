#include "game_state_manager.h"
#include "colors.h"
#include "game_exception.h"
#include "../utils/xml_parser/xml_parser.h"

#include "main_menu.h"
#include "pause_state.h"
#include "../game_book/page_types/story.h"

GameStateManager::GameStateManager()
    : current_state(0), shall_run(true), player(nullptr)
{
    InitColors();

    // create states
    menu_state = 0;
    states[menu_state] = std::make_unique<MainMenu>(this);
    pause_state = 1;
    states[pause_state] = std::make_unique<PauseState>(this);
    game_state = 2;
    states[game_state] = std::make_unique<Page>(this);

    // add cross available helper screens
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
        text.NewLine("Up Down navigate in menu   ");
        text.NewLine("j   k   scroll window      ");
        text.NewLine("Enter   select             ");
        text.NewLine("  p     pause (in game)    ");
        text.NewLine("  i     inventory (in game)");
    }

    {
        auto & text = wm.AddScreen("about").
                      AddWindow<graphics::Textbox>(
            "about info",
            graphics::XPercent(77),
            3,
            graphics::XPercent(33) / 2,
            about_color
        );
        text.AppendText("By Vitalii Baturevych");
    }

    wm.AddScreen("exception").
    AddWindow<graphics::Textbox>(
        "err",
        graphics::XPercent(80),
        graphics::YPercent(10),
        graphics::XPercent(10),
        error_color
    );
}

inline void GameStateManager::SwitchState(size_t state_code, Notify notification)
{
    current_state = state_code;
    states[current_state]->GetNotification(notification);
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

inline void GameStateManager::Stop()
{
    shall_run = false;
}

void GameStateManager::PopUp(const std::string & screen){
    wm.SelectScreen(screen);
    wm.Draw();
    getch();
    SwitchState(current_state);
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
    else
        throw GameException("file is not in correct format. Page must have a type");

}
