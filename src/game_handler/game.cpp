#include "game.h"
#include "../game_book/page_types/story.h"
#include "../utils/xml_parser/xml_parser.h"
#include "game_state_manager.h"
#include "game_exception.h"

Game::Game(GameStateManager * manager)
    : IGameState(manager),
      player(nullptr),
      current(0)
{
}

void Game::Load()
{
    auto doc = xml::Parser::GetDoc("save.xml");
    player.reset(new Creature(doc.Root().Child("player")));
    TurnTo(doc.Root().Child("page").Text());
}

void Game::Save() const
{
    if (page[current].get() == nullptr)
        throw GameException("saving game, but we are not in it");

    auto root = xml::Tag("save");
    root.AddChild(page[current]->Serialize());
    root.AddChild(player->Serialize());
    auto doc = xml::Parser::NewDoc("save.xml", root);
    doc.Save();

}

void Game::TurnTo(const std::string & filename)
{
    auto doc = xml::Parser::GetDoc(filename);
    auto root = doc.Root();
    if (root.Name() != "page")
        throw GameException("root tag of a file must be <page type=\"page_tyepe\">");

    std::string type = root.Prop("type");
    current = current == 0 ? 1 : 0;
    if (type == "story")
        page[current].reset(new Story(root, this));
    else
        throw GameException("file is not in correct format. Page must have a type");
}


bool Game::Reacted(int input)
{
    if (page[current]->Reacted(input))
        return true;
    else if (input == 'p')
    {
        gsm->SwitchState(pause_state);
        return true;
    }
    
    return gsm->DefaultReactedToInput(input, page[current]->BottomWindow(), page[current]->TopWindow()); 
}

void Game::GetNotification(Notify notification)
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
            player.reset(new Creature());
            TurnTo("book/begin.xml");
            break;
        case Notify::Continue:
            if (!page[current].get() || !player.get())
                throw GameException("nothing to continue");
            break;
            
        default:
            throw std::invalid_argument("game got wrong notification");
    }
}
