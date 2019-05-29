#ifndef __GAMEBOOK_ITEMS_FOOD__
#define __GAMEBOOK_ITEMS_FOOD__

#include "../item.h"

class Food : public Item
{
    private:
        int heal_value;
    public:
        Food(const xml::Tag & t);
        xml::Tag Serialize() const override;
};

#endif
