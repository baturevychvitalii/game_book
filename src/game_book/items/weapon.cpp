#include "weapon.h"
#include "../creature.h"
#include "../../game_handler/colors.h"

Weapon::Weapon(
	IChangeable * parent,
	size_t width,
	short y,
	short x,
	short active_color,
	short inactive_color,
	const xml::Tag & t
)
	: Item(parent, width, y, x, active_color, inactive_color, t),
	damage(std::stoi(t.Prop("damage")))
{
	SetNameColor(red_on_black);
	NewLine("damage: " + std::to_string(damage));
}

xml::Tag Weapon::Serialize() const
{
	return Item::Serialize().AddProp("damage", damage);
}

size_t Weapon::Use(size_t charges, Creature * creature)
{
	return Item::Use(charges, creature);
}
