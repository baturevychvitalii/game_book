#ifndef __GAMEBOOK_ITEM__
#define __GAMEBOOK_ITEM__


#include "../utils/xml_parser/ISerializable.h"
#include "../utils/graphics/button.h"

class Creature;

class Item : ISerializable, public graphics::Button
{
	const std::string type;
	const std::string name;
	size_t durability;
	size_t line_with_durability;
	const size_t price_per_durability;

	protected:
		size_t IdxOfLineAfterName() const {return line_with_durability;}
	
    public:
        Item(
            IChangeable * parent,
            size_t width,
            short y,
            short x,
            short active_color,
            short inactive_color,
            const xml::Tag & t);
        Item() = delete;
        Item(const Item & other) = delete;
        Item & operator=(const Item & other) = delete;
        
        virtual size_t Use(size_t charges, Creature * creature);
        size_t Price() const;
        xml::Tag Serialize() const override;
};

#endif
