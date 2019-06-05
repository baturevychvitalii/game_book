#ifndef __GAMEBOOK_INVENTORY__
#define __GAMEBOOK_INVENTORY__

#include "item.h"
#include "../utils/graphics/menu.h"

class Inventory : public ISerializable, public graphics::Menu<Item>
{
	// size_t MinHeight() const override;
    public:
        Inventory(const Inventory & other) = delete;
        Inventory & operator=(const Inventory & other) = delete;
        
        Inventory(const xml::Tag & t);

        Inventory();

        xml::Tag Serialize() const override;
};

#endif
