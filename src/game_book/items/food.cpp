#include "food.h"
#include "../creature.h"
#include "../../game_handler/colors.h"

Food::Food(
	IChangeable * parent,
	size_t width,
	short y,
	short x,
	short active_color,
	short inactive_color,
	const xml::Tag & t
)
    : Item(parent, width, y, x, active_color, inactive_color, t),
    heal_value(std::stoi(t.Prop("heal")))
{
	SetNameColor(green_on_black);
	NewLine("heal: " + std::to_string(heal_value));
}

xml::Tag Food::Serialize() const
{
    return Item::Serialize().AddProp("heal", std::to_string(heal_value));
}

size_t Food::Use(size_t charges, Creature * creature)
{
    size_t charges_to_use = Item::Use(charges, creature);
	creature->ChangeHealth(charges_to_use * heal_value);
	return charges_to_use;
}
