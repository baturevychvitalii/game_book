#ifndef __GAMEBOOK_INVENTORY__
#define __GAMEBOOK_INVENTORY__

#include <vector>

#include "item.h"

class Inventory : ISerializable
{
    private:
        unsigned max_items;
        std::vector<std::unique_ptr<Item>> items;
    public:
        static const unsigned size_limit;
        Inventory(const xml::Tag & t);
        Inventory();
        Inventory(const Inventory & other) = delete;
        Inventory & operator=(const Inventory & other) = delete;
        ~Inventory() = default;

        void GetItemFrom(size_t idx, Inventory & other);
        void RemoveItem(size_t idx);

        xml::Tag Serialize() const override;
};

#endif
