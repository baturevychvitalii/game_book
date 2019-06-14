#include "fixer.h"
#include "../inventory.h"
#include "../../game_handler/colors.h"
 
Fixer::Fixer(
	IChangeable * parent,
	size_t width,
	short y,
	short x,
	short active_color,
	short inactive_color,
	const xml::Tag & t
)
    : Item(parent, width, y, x, active_color, inactive_color, t),
    restores(std::stoi(t.Prop("fix")))
{
	SetNameColor(yelow_on_black);
	NewLine("fix: " + std::to_string(restores));
}

xml::Tag Fixer::Serialize() const
{
    return Item::Serialize().AddProp("fix", restores);
}

size_t Fixer::Use(size_t charges, Creature *potential_opponent)
{
	size_t charges_to_use = Item::Use(charges);
	for (size_t i = 0; i < GetInventory()->Size()  ; i++)
	{
		(*GetInventory())[i].Fix(charges_to_use * restores);
	}

	return charges_to_use;
}
