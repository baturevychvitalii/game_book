#include "food.h"
#include "../creature.h"

Food::Food(const xml::Tag & t)
    : Item(t),
    heal_value(std::stoi(t.Prop("heal")))
{
}

xml::Tag Food::Serialize() const
{
    return Item::Serialize().AddProp("heal", std::to_string(heal_value));
}

size_t Food::Use(size_t charges, Creature * creature)
{
    size_t used = Item::Use(charges, creature);
    
}
