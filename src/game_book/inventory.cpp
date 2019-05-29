#include "inventory.h"

Inventory::Inventory()
    : max_items(3)
{
}

xml::Tag Inventory::Serialize() const
{
    auto tag = xml::Tag("inventory");
    tag.AddChild("max_items").AddText(std::to_string(max_items));
    for (auto & item : items)
    {
        tag.AddChild(item->Serialize());
    }
    return tag;
}
