#ifndef __GAMEBOOK_ITEMS_WEAPON__
#define __GAMEBOOK_ITEMS_WEAPON__

#include "../item.h"

/**
weapons are mainly used to deal damage
difference between weapon and food is that when using
it on a creature's health instead of adding it's unique
value it subtracts it
*/
class Weapon : public Item
{
    int damage;
    size_t Use(size_t charges, Creature * creature) override;
    public:
		/**
		constructs the weapon, from an xml tag.
		first arguments are forwarded to button constructor
		*/
        Weapon(
			IChangeable * parent,
			size_t width,
			short y,
			short x,
			short active_color,
			short inactive_color,
			const xml::Tag & t
		);

		/**
		serializes weapon to xml tag
		*/
        xml::Tag Serialize() const override;
};

#endif
