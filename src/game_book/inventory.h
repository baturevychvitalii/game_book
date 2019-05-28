#ifndef __GAMEBOOK_INVENTORY__
#define __GAMEBOOK_INVENTORY__

#include <vector>

#include "item.h"

class Inventory : ISerializable
{
    private:
        unsigned max_items;
        std::vector<Item *> items;
    public:
        static const unsigned size_limit;
        Inventory(const xml::Tag & t);
        Inventory(const Inventory & other) = delete;
        Inventory & operator=(const Inventory & other) = delete;
        ~Inventory();

        xml::Tag Serialize() const override;
};

const unsigned Inventory::size_limit = 16;

#endif
