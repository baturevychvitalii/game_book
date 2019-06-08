#include "fixer.h"
#include "../creature.h"
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
    return Item::Serialize().AddProp("fix", std::to_string(restores));
}

size_t Fixer::Use(size_t charges, Creature * creature)
{
	size_t charges_to_use = Item::Use(charges, creature);
	Inventory & inve = creature->GetInventory();
	for (size_t i = 0; i < inve.Size(); i++)
	{
		Item & curr = inve[i];
		if (curr.GetType() != "fixer")
			curr.Fix(restores * charges_to_use);
	}
	
	return charges_to_use;
}
