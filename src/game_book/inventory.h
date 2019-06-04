#ifndef __GAMEBOOK_INVENTORY__
#define __GAMEBOOK_INVENTORY__

#include "item.h"
#include "../utils/graphics/menu.h"

class Inventory : public ISerializable, public graphics::Menu<Item>
{
    private:
        size_t max_items;
    public:
        Inventory(const Inventory & other) = delete;
        Inventory & operator=(const Inventory & other) = delete;
        
        Inventory(const xml::Tag & t);

        Inventory();
		void ChangeMax(int dx);

        xml::Tag Serialize() const override;
};

#endif
