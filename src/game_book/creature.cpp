#include "creature.h"

Creature::Creature()
    : name("Lorry"), health(77), cash(7)
{
}

xml::Tag Creature::Serialize() const
{
    auto tag = xml::Tag("player");
    tag.AddChild("health").AddText(std::to_string(health));
    tag.AddChild("cash").AddText(std::to_string(cash));
    tag.AddChild(inventory.Serialize());
    return tag;
}
