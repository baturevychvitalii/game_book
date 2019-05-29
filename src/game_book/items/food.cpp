#include "food.h"

Food::Food(const xml::Tag & t)
    : Item(t),
    heal_value(std::stoi(t.Prop("value")))
{
}

xml::Tag Food::Serialize() const
{
    return Item::Serialize().AddProp("value", std::to_string(heal_value));
}
