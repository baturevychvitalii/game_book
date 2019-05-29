#include "creature.h"

Creature::Creature()
    : name("Lorry"), health(77), cash(7)
{
}

Creature::Creature(const xml::Tag & tag)
    : name(tag.Prop("name")),
    health(std::stoi(tag.Child("health").Text())),
    cash(std::stoi(tag.Child("cash").Text())),
    inventory(tag.Child("inventory"))
{
}

xml::Tag Creature::Serialize() const
{
    auto tag = xml::Tag("player");
    tag.AddProp("name", name);
    tag.AddChild("health").AddText(std::to_string(health));
    tag.AddChild("cash").AddText(std::to_string(cash));
    tag.AddChild(inventory.Serialize());
    return tag;
}
