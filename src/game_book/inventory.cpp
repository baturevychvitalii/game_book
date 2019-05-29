#include "inventory.h"
#include "items/food.h"

Inventory::Inventory()
    : max_items(3)
{
}

Inventory::Inventory(const xml::Tag & t)
    : max_items(std::stoi(t.Child("max_items").Text()))
{
    std::string type;
    for (const auto & tag : t.GetVector("item"))
    {
        type = t.Prop("type");
        if (type == "food")
            items.emplace_back(new Food(tag));
    }
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
