#include "IGameState.h"
#include "game_state_manager.h"

IGameState::IGameState(GameStateManager * game_state_manager,
                       const std::string & screen_id)
    : gsm(game_state_manager),
      wm(gsm->GetWindowManager()),
      screen(wm.AddScreen(screen_id))
{
}

IGameState::~IGameState()
{
    wm.RemoveScreen(screen);
}

void IGameState::Draw()
{
    wm.SelectScreen(screen);
    wm.Draw();
}
