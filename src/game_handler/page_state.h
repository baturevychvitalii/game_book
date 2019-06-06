#ifndef __PAGE_STATE__
#define __PAGE_STATE__

#include "../game_book/creature.h"
#include "IGameState.h"

/**
base of all pages
*/
class Page : public ISerializable, public IGameState
{
    const std::string filename;
    std::vector<std::pair<std::string, std::string>> crossroads;

    xml::Tag Serialize() const override;


    void Save() const;
    void Load();
    void New();
	
	protected:
		bool Reacted(int input) override;
    	void ProcessMenuSelection(graphics::menu_base * to_test) override;
    	void GetNotification(Notify notification) override;

    public:
        Page() = delete;
        Page(const Page & p) = delete;
        Page & operator=(const Page & p) = delete;

        /**
		called only once, when GSM is being constructed.
		Will let us to accept notification to go to new game or to load game
		*/
        Page(GameStateManager * manager);

        /**
		regular page, loaded from an xml file
		*/
        Page(const xml::Tag & root, GameStateManager * manager);

};

#endif
