#include "creature.h"
#include "../game_handler/colors.h"
#include "../utils/graphics/status_bar.h"

Creature::Creature(
	const std::string & nome,
	size_t heal,
	size_t max_heal,
	size_t cash,
	Inventory * inv
)
	: name(nome), health(heal), max_health(max_heal), cash(cash),
	inventory(inv),
	status(new graphics::Group<graphics::Textbox>(nullptr, graphics::max_x, 0, 0, white_on_magneta, 2, 0, 1)),
	DefaultDamage(10)
{
	status->EmplaceBack<graphics::StatusBar>(
		status_health_active_color,
		status_health_inactive_color,
		health,
		max_health
	).AppendText("health", status_health_active_color);

	status->EmplaceBack<graphics::Textbox>(status_theme_color).NewLine(name + " $" + std::to_string(cash));
	status->SetDrawBackground();
	status->Commit();
}

Creature::Creature()
	: Creature("Lorry", 77, 111, 777, new Inventory())
{
}

Creature::Creature(const xml::Tag & tag)
	: Creature(
		tag.Prop("name"),
		std::stoi(tag.Child("health").Text()),
		std::stoi(tag.Child("max_health").Text()),
		std::stoi(tag.Child("cash").Text()),
		new Inventory(tag.Child("inventory"))
	)
{
}

xml::Tag Creature::Serialize() const
{
    auto tag = xml::Tag("player").AddProp("name", name);
    tag.AddChild("health").AddText(std::to_string(health));
    tag.AddChild("max_health").AddText(std::to_string(max_health));
    tag.AddChild("cash").AddText(std::to_string(cash));
    tag.AddChild(inventory->Serialize());
    return tag;
}

Inventory & Creature::GetInventory()
{
    return *inventory;
}

graphics::Group<graphics::Textbox> & Creature::GetStatusBar()
{
	return *status;
}

size_t Creature::Budget() const
{
	return cash;
}

bool Creature::ChangeBudget(int value)
{
	if (value < 0 && std::abs(value) > cash)
		return false;

	cash += value;
	(*status)[1].AlterLineText(0, name + " $" + std::to_string(cash));
	return true;
}

bool Creature::IsAlive() const
{
	return health > 0;
}

Creature & Creature::ChangeHealth(int value)
{
	int result = static_cast<int>(health) + value;
	if (result > static_cast<int>(max_health))
		health = max_health;
	else if (result < 0)
		health = 0;
	else
		health = result;
	
	static_cast<graphics::StatusBar &>((*status)[0]).SetAct(health);

	return *this;
}
