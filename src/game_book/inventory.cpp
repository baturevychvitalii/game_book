#include "inventory.h"
#include "../game_handler/colors.h"
#include "items/food.h"
#include "items/weapon.h"
#include "../game_handler/game_exception.h"

static const size_t inventory_colomns = 3;

Inventory::Inventory()
	: graphics::Menu<Item>(nullptr, graphics::max_x, 0, 0, menu_bg_color, menu_active_color, menu_inactive_color, inventory_colomns)
{
	Commit();
}

Inventory::Inventory(const xml::Tag & t)
    : Inventory()
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

// size_t Inventory::MinHeight() const
// {
// 	return std::max(graphics::max_y, Menu::MinHeight());
// }

xml::Tag Inventory::Serialize() const
{
    auto tag = xml::Tag("inventory");
	for (size_t i = 0; i < Size(); i++)
	{
		tag.AddChild((*this)[i].Serialize());
	}

    return tag;
}
