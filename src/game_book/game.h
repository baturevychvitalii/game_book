#ifndef __GAMEBOOK_GAME__
#define __GAMEBOOK_GAME__
#include "creature.h"
#include "page.h"



class Game
{
    std::unique_ptr<Creature> player;

    
    size_t MainMenu() const;
    std::string Load();
    std::unique_ptr<Page> GetPage(const std::string & filename);
    void Play(std::string from_page);
    public:
        Game();
        Game(const Game & other) = delete;
        Game & operator=(const Game & other) = delete;
        ~Game() = default;
        void StartFromMainMenu();
};

#endif
