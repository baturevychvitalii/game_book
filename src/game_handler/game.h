#ifndef __GAMEBOOK_GAME__
#define __GAMEBOOK_GAME__

#include "IGameState.h"

class Page;
class Creature;

class Game : public IGameState
{
    friend class Page;
    std::unique_ptr<Creature> player;
    // when pages are turning we shall keep both of them, because
    // crossroads are inside page
    std::unique_ptr<Page> page[2];
    size_t current;

    void Load();
    void Save() const;
    void TurnTo(const std::string & filename);

    void GetNotification(Notify notification) override;
    bool Reacted(int input) override;
    public:
        Game() = delete;
        Game(const Game & other) = delete;
        Game & operator=(const Game & other) = delete;
        
        Game(GameStateManager * manager);
};

#endif
