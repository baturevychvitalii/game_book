#ifndef __GAMEBOOK_ITEM__
#define __GAMEBOOK_ITEM__


#include "../utils/xml_parser/ISerializable.h"
#include "../utils/graphics/button.h"

class Creature;

/**
base of all items. can only be in inventory
*/
class Item : ISerializable, public graphics::Button
{
	const std::string type;
	const std::string name;
	size_t durability;
	size_t line_with_durability;
	const size_t price_per_durability;

	protected:
		void SetNameColor(short color);
	
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
        
		/**
		@return name of this type in string format
		*/
		const std::string & GetType() const;

		/**
		applies this item to provided creature
		@param charges how many charges to use.
		@param creature creature, to which this item will be applied
		@return how many charges can be used
		*/
        virtual size_t Use(size_t charges, Creature * creature);

		void Fix(size_t charges){durability += charges;}

		/**
		@return price of the item based on ppd 'price per durability' value
		*/
        size_t Price() const;

		/**
		serializes item base to xml tag
		*/
        xml::Tag Serialize() const override;
};

#endif
