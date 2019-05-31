#include "game_state_manager.h"
#include "colors.h"
#include "main_menu.h"
#include "pause_state.h"
#include "game.h"

GameStateManager::GameStateManager()
    : current_state(0), shall_run(true)
{
    states.reserve(7);
    InitColors();

    // create states
    menu_state = 0;
    states.emplace_back(std::make_unique<MainMenu>(this));
    pause_state = 1;
    states.emplace_back(std::make_unique<PauseState>(this));
    game_state = 2;
    states.emplace_back(std::make_unique<Game>(this));

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

bool GameStateManager::Reacted(int input)
{
    switch (input)
    {
        case 'k':
            if (states[current_state]->BotWindow().LowestPoint() > graphics::max_y)
                states[current_state]->Move(graphics::Direction::Down, 3);
            break;
        case 'j':
            if (states[current_state]->TopWindow().HighestPoint() < 0)
                states[current_state]->Move(graphics::Direction::Up, 3);
            break;
        default:
            return false;
    }

    return true;
}

