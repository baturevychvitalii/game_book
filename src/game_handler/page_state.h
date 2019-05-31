#ifndef __PAGE_STATE__
#define __PAGE_STATE__

#include "../game_book/creature.h"
#include "IGameState.h"

class Page : public ISerializable, public IGameState
{
    const std::string filename;
    std::vector<std::pair<std::string, std::string>> crossroads;

    xml::Tag Serialize() const override;

    void GetNotification(Notify notification) override;
    bool Reacted(int input) override;
    void StandardManuHandlerProcess(graphics::Menu * to_test) override;

    void Save() const;
    void Load();
    void New();

    public:
        Page() = delete;
        Page(const Page & p) = delete;
        Page & operator=(const Page & p) = delete;

        // start page, created to get notification and load normal page
        Page(GameStateManager * manager);

        // normal page, loaded from file
        Page(const xml::Tag & root, GameStateManager * manager);

};

#endif
