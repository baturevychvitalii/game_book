#ifndef __ITEM_FIXER__
#define __ITEM_FIXER__

#include "../item.h"

class Fixer : public Item
{
    size_t restores;
    size_t Use(size_t charges, Creature * creature) override;
    public:
		/**
		constructs item from xml tag
		*/
        Fixer(
			IChangeable * parent,
			size_t width,
			short y,
			short x,
			short active_color,
			short inactive_color,
			const xml::Tag & t
		);

		/**
		serializes fixer's properties to xml tag
		*/
        xml::Tag Serialize() const override;
};

#endif
