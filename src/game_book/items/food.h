#ifndef __GAMEBOOK_ITEMS_FOOD__
#define __GAMEBOOK_ITEMS_FOOD__

#include "../item.h"

class Food : public Item
{
    int heal_value;
    size_t Use(size_t charges, Creature * creature) override;
    public:
        Food(const xml::Tag & t);
        xml::Tag Serialize() const override;
};

#endif
