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

Inventory & Inventory::StealItemFrom(Inventory & other, size_t idx)
{
	AddOption(
		other.ReleaseOption(idx)
	);

	return *this;
}

Inventory & Inventory::StealWholeInventory(Inventory & other)
{
	while (other.Size() > 0)
	{
		StealItemFrom(other, 0);
	}
	
	return *this;
}

xml::Tag Inventory::Serialize() const
{
    auto tag = xml::Tag("inventory");
	for (size_t i = 0; i < Size(); i++)
	{
		tag.AddChild((*this)[i].Serialize());
	}

    return tag;
}
