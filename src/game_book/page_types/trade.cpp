#include "trade.h"

Trade::Trade(const xml::Tag & root, GameStateManager * manager)
    : Page(root, manager), trader(root.Child("trader"))
{

}
