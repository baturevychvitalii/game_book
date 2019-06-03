#include "creature.h"

Creature::Creature(const std::string & name, unsigned max_health, unsigned cash)
    : name(name), health(max_health), max_health(max_health), cash(cash), inventory(5)
{
}

Creature::Creature(const xml::Tag & tag)
    : name(tag.Prop("name")),
    health(std::stoi(tag.Child("health").Text())),
    max_health(std::stoi(tag.Child("max_health").Text())),
    cash(std::stoi(tag.Child("cash").Text())),
    inventory(tag.Child("inventory"))
{
}

xml::Tag Creature::Serialize() const
{
    auto tag = xml::Tag("player").AddProp("name", name);
    tag.AddChild("health").AddText(std::to_string(health));
    tag.AddChild("max_health").AddText(std::to_string(max_health));
    tag.AddChild("cash").AddText(std::to_string(cash));
    tag.AddChild(inventory.Serialize());
    return tag;
}

Inventory & Creature::Inventory()
{
    return inventory;
}
