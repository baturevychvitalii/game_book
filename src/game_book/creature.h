#ifndef __GAMEBOOK_CREATURE__
#define __GAMEBOOK_CREATURE__


#include "inventory.h"

class Creature : ISerializable
{
    private:
		Creature(
			const std::string & name,
			size_t heal,
			size_t max_heal,
			size_t cash,
			Inventory * inv
		);

        const std::string name;
        size_t health, max_health;
        size_t cash;
        Inventory * inventory;
		graphics::Group<graphics::Textbox> * status;
    public:
        Creature(const Creature & other) = delete;
        Creature & operator=(const Creature & other) = delete;
        ~Creature() = default;

        Creature();
        Creature(const xml::Tag & tag);
        xml::Tag Serialize() const override;

        Inventory & GetInventory();
		graphics::Group<graphics::Textbox> & GetStatusBar();
		
		const size_t DefaultDamage;
		size_t Budget() const;
		bool ChangeBudget(int value);
		bool IsAlive() const;
		Creature & ChangeHealth(int value);
};

#endif
