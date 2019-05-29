#include "item.h"

Item::Item(const xml::Tag & t)
    : name(t.Prop("name")),
    durability(std::stoi(t.Prop("charges"))),
    price_per_durability(std::stoi(t.Prop("ppd")))
{
}

xml::Tag Item::Serialize() const
{
    return xml::Tag("item").
    AddProp("name", name).
    AddProp("charges", std::to_string(durability)).
    AddProp("ppd", std::to_string(price_per_durability));
}
