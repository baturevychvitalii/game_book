#include "item.h"
#include "inventory.h"

Item::Item(
	IChangeable * parent,
	size_t width,
	short y,
	short x,
	short active_color,
	short inactive_color,
	const xml::Tag & t)
    : graphics::Button(parent, width, y, x, active_color, inactive_color),
	type(t.Prop("type")),
    name(t.Prop("name")),
    durability(std::stoi(t.Prop("charges"))),
    price_per_durability(std::stoi(t.Prop("ppd")))
{
	// try to see if the item is fixible. default true
	try
	{
		fixible = std::stoi(t.Prop("fixible"));
	}
	catch(std::exception & e)
	{
		fixible = true;
	}

	AppendText(name);
	line_with_durability = NewLine((fixible ? "#f" : "#u") + std::to_string(durability));
	NewLine("$" + std::to_string(Price()));
}

xml::Tag Item::Serialize() const
{
    return xml::Tag("item").
	AddProp("type", type).
    AddProp("name", name).
    AddProp("charges", durability).
	AddProp("fixible", fixible).
    AddProp("ppd", price_per_durability);
}

Creature * Item::GetOwner() const
{
	return GetInventory()->GetOwner();
}

Inventory * Item::GetInventory() const
{
	//								  Group  -->  Menu
	return static_cast<Inventory *>(GetParent()->GetParent());
}

size_t Item::Use(size_t charges, Creature * potential_opponent)
{
	// we can't use more charges than we have
    size_t to_use = std::min(durability, charges);
    durability -= to_use;
	UpdateDurability();
    return to_use;
}

const std::string & Item::GetType() const
{
	return type;
}

size_t Item::Price() const
{
    return price_per_durability * durability;
}

void Item::UpdateDurability()
{
	AlterLineText(line_with_durability, (fixible ? "#f" : "#u") + std::to_string(durability));
	AlterLineText(line_with_durability + 1, "$" + std::to_string(Price()));
}

size_t Item::Durability() const
{
	return durability;
}

void Item::SetFixible(bool value)
{
	fixible = value;
	UpdateDurability();
}

bool Item::IsFixable()const
{
	return fixible;
}	

void Item::Fix(size_t charges)
{
	if (fixible)
	{
		durability += charges;
		UpdateDurability();
	}
}

void Item::SetNameColor(short color)
{
	for (size_t i = 0; i < line_with_durability; i++)
	{
		AlterLineColor(i, color);
	}
}

