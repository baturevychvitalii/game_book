#include "item.h"

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
	AppendText(name);
	line_with_durability = NewLine("charges: " + std::to_string(durability));
	NewLine("$" + std::to_string(Price()));
}

xml::Tag Item::Serialize() const
{
    return xml::Tag("item").
	AddProp("type", type).
    AddProp("name", name).
    AddProp("charges", std::to_string(durability)).
    AddProp("ppd", std::to_string(price_per_durability));
}

size_t Item::Use(size_t charges, Creature * c)
{
    size_t to_use = std::min(durability, charges);
    durability -= to_use;
	AlterLineText(line_with_durability, "#" + std::to_string(durability));
	AlterLineText(line_with_durability + 1, "$" + std::to_string(Price()));
    return to_use;
}

size_t Item::Price() const
{
    return price_per_durability * durability;
}
