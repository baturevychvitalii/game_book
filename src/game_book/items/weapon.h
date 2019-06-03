#ifndef __GAMEBOOK_ITEMS_WEAPON__
#define __GAMEBOOK_ITEMS_WEAPON__

#include "../item.h"

class Weapon : public Item
{
    int damage;
    size_t Use(size_t charges, Creature * creature) override;
    public:
        Weapon(const xml::Tag & t);
        xml::Tag Serialize() const override;
};

#endif
