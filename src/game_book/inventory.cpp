#include "inventory.h"
#include "../game_handler/colors.h"
#include "items/food.h"
#include "items/weapon.h"
#include "../game_handler/game_exception.h"

static const size_t inventory_colomns = 3;

Inventory::Inventory(const xml::Tag & t)
    : graphics::Menu<Item>(nullptr, graphics::max_x, 0, 0, inventory_bg_color, item_selected_color, item_unselected_color, inventory_colomns),
	max_items(std::stoi(t.Child("max_items").Text()))
{
    std::string type;
    for (const auto & item : t.GetVector("item"))
    {
        type = item.Prop("type");
        if (type == "food")
			AddOption<Food>(item);
		else if(type == "weapon")
			AddOption<Weapon>(item);
		else
			throw GameException("unsupported item type");
    }

	Commit();
}

Inventory::Inventory()
	: graphics::Menu<Item>(nullptr, graphics::max_x, 0, 0, inventory_bg_color, item_selected_color, item_unselected_color, inventory_colomns),
	max_items(3)
{
	Commit();
}

size_t Inventory::MinHeight() const
{
	return std::max(Menu::MinHeight(), graphics::max_y);
}


xml::Tag Inventory::Serialize() const
{
    auto tag = xml::Tag("inventory");
    tag.AddChild("max_items").AddText(std::to_string(max_items));
	for (size_t i = 0; i < Size(); i++)
	{
		tag.AddChild((*this)[i].Serialize());
	}

    return tag;
}
