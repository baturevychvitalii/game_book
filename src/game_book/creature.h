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
			size_t damage,
			size_t cash,
			Inventory * inv
		);

		const std::string name;
		size_t health, max_health;
		size_t default_damage;
		size_t cash;
		Inventory * inventory;
		graphics::Group<graphics::Textbox> * status;
	public:
		/*
		 * Why would we want to copy creature? it is nonesense
		 */
		Creature(const Creature & other) = delete;
		Creature & operator=(const Creature & other) = delete;
		~Creature() = default;

		/*
		 * Creates player when New game is chosen in Main Menu
		 */
		Creature();

		/*
		 * Deserializes creature from xml tag.
		 * It happens when either we saved our game and want to get a player as he was,
		 * or when page is in fight state and we have an enemy
		 */
		Creature(const xml::Tag & tag);

		/*
		 * Serializes Creature to xml tag
		 */
		xml::Tag Serialize() const override;

		/*
		 * Returns a reference to creatures inventory
		 */
		Inventory & GetInventory();

		/*
		 * Returns a reference to creatures status bar, which displays health of a creature,
		 * it's name and $$$
		 */
		graphics::Group<graphics::Textbox> & GetStatusBar();
			
		/*
		 * Damage which is dealt by hand
		 */
		size_t DefaultDamage() const;

		/*
		 * cash owned by a creature
		 */
		size_t Budget() const;

		/*
		 * try alter cash of a creature
		 * @param value value will += to current cash
		 * @return true if this cash operation is possible, false if not enough cash
	 	 */
		bool ChangeBudget(int value);

		/*
		 * Check if creature is alive
		 * @return obvious
		 */
		bool IsAlive() const;

		/*
		 * alter health of a creature
		 * @param value if positive - will increase creatures health, decrease otherwise
		 */
		Creature & ChangeHealth(int value);
};

#endif
