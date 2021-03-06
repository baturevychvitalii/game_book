#ifndef __GAMEBOOK_INVENTORY__
#define __GAMEBOOK_INVENTORY__

#include "item.h"
#include "../utils/graphics/menu.h"

class Creature;

/*
 * Inventory holds Items as buttons
 */
class Inventory : public ISerializable, public graphics::Menu<Item>
{
	Creature * owner;
	
    public:
		/*
		 * Why would we copy the inventory
		 */
        Inventory(const Inventory & other) = delete;
        Inventory & operator=(const Inventory & other) = delete;
        
		/*
		 * deserializes inventory from an xml tag
		 * @param t xml tag which represents an item
		 */
        Inventory(const xml::Tag & t, Creature * owner);

		/*
		 * Creates empty inventory.
		 * Used only when New game is selected, new player is created with default inventory
		 */
        Inventory(Creature * owner);

		/*
		 * transfers item from some other inventory to this one
		 * @param other inventory from which item will be taken
		 * @param idx idx of item to take
		 */
		Inventory & StealItemFrom(Inventory & other, size_t idx);

		/*
		 * transfers all items from other inventory
		 */
		Inventory & StealWholeInventory(Inventory & other);

		/*
		 * @return owner of this inventory
		 */
		Creature * GetOwner() const;

		/*
		 * serializes inventory to an xml tag
		 */
        xml::Tag Serialize() const override;
};

#endif
