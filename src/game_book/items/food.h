#ifndef __GAMEBOOK_ITEMS_FOOD__
#define __GAMEBOOK_ITEMS_FOOD__

#include "../item.h"

class Food : Item
{
    private:
        int heal_value;
    public:
        Food(const xml::Tag & t);
        ~Food();
        xml::Tag Serialize() const override;
};

#endif
