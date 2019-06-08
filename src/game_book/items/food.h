#ifndef __GAMEBOOK_ITEMS_FOOD__
#define __GAMEBOOK_ITEMS_FOOD__

#include "../item.h"

/**
is supposed to heal the creature, on which is being used
*/
class Food : public Item
{
    int heal_value;
    size_t Use(size_t charges, Creature * creature) override;
    public:
		/**
		constructs item from xml tag
		*/
        Food(
			IChangeable * parent,
			size_t width,
			short y,
			short x,
			short active_color,
			short inactive_color,
			const xml::Tag & t
		);

		/**
		serializes food's properties to xml tag
		*/
        xml::Tag Serialize() const override;
};

#endif
