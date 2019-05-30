#include "game_state_manager.h"
#include "colors.h"
#include "main_menu_state.h"

GameStateManager::GameStateManager()
    : current_state(0), shall_run(true)
{
    states.reserve(7);
    InitColors();

    // create states
    menu_state = 0;
    states.emplace_back(MainMenuState(this));
    pause_state = 1;

    game_state = 2;

    // add cross available helper screens
    {
        auto & text = wm.AddScreen("controls").
                      AddWindow<graphics::Textbox>(
            "controls info",
            graphics::Window::max_x,
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
            graphics::Window::XPercent(77),
            3,
            graphics::Window::XPercent(33) / 2,
            about_color
        );
        text.AppendText("By Vitalii Baturevych");
    }

    wm.AddScreen("exception").
    AddWindow<graphics::Textbox>(
        "err",
        graphics::Window::XPercent(80),
        graphics::Window::YPercent(10),
        graphics::Window::XPercent(10),
        error_color
    );
}

inline void GameStateManager::SwitchState(size_t state_code, size_t arg)
{
    current_state = state_code;
    states[current_state]->Select(arg);
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

bool GameStateManager::DefaultReactedToInput(int input, graphics::Window & bot, graphics::Window & top)
{
    switch (input)
    {
        case 'k':
            if (bot.LowestPoint() > graphics::Window::max_y)
                wm.Move(graphics::Direction::Up, 3);
            break;
        case 'j':
            if (top.HighestPoint() < 0)
                wm.Move(graphics::Direction::Down, 3);
            break;
        default:
            return false;
    }

    return true;
}

