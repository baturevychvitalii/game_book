#ifndef __GAMEBOOK_INVENTORY__
#define __GAMEBOOK_INVENTORY__

#include <vector>

#include "item.h"
#include "../utils/graphics/group.h"

class Inventory : public ISerializable, public graphics::Menu<Item>
{
    private:
        size_t max_items;
    public:
        Inventory() = delete;
        Inventory(const Inventory & other) = delete;
        Inventory & operator=(const Inventory & other) = delete;
        
        Inventory(
			IChangeable * parent,
			size_t width,
			short y,
			short x,
			short bg_color,
			
			const xml::Tag & t);
        ~Inventory() = default;
        Inventory(size_t max_items);

		void ChangeMax(int dx);

        xml::Tag Serialize() const override;
};

#endif
