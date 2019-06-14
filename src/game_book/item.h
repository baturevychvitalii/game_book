#ifndef __GAMEBOOK_ITEM__
#define __GAMEBOOK_ITEM__


#include "../utils/xml_parser/ISerializable.h"
#include "../utils/graphics/button.h"

class Creature;
class Inventory;

/*
 * base of all items. can only be in inventory
 */
class Item : ISerializable, public graphics::Button
{
	const std::string type;
	const std::string name;
	size_t durability;
	bool fixible;
	const size_t price_per_durability;
	size_t line_with_durability;

	void UpdateDurability();

	protected:
		void SetNameColor(short color);
		Inventory * GetInventory() const;
	
    public:
        Item(
            IChangeable * parent,
            size_t width,
            short y,
            short x,
            short active_color,
            short inactive_color,
            const xml::Tag & t);
        Item() = delete;
        Item(const Item & other) = delete;
        Item & operator=(const Item & other) = delete;
        
		/*
		 * @return name of this type in string format
		 */
		const std::string & GetType() const;

		/*
		 * @return owner of inventory, where this item is stored
		 */
		Creature * GetOwner() const;

		/*
		 * applies this item to proper creature. Derived virtual override of
		 * this method will decide to whom it shall be applied.
		 * @param charges how many charges we want to use
		 * @param potential_opponent will be chosen if an item is for example Weapon
		 * @return how many charges can be used
		 */
        virtual size_t Use(size_t charges = 1, Creature * potential_opponent = nullptr);

		void SetFixible(bool value = true);

		/*
		 * @return true if item is fixable
		 */
		bool IsFixable() const;

		/*
		 * increase durability of this item
		 */
		void Fix(size_t charges);

		/*
		 * @return price of the item based on ppd 'price per durability' value
		 */
        size_t Price() const;

		size_t Durability() const;

		/*
		 * serializes item base to xml tag
		 */
        xml::Tag Serialize() const override;
};

#endif
