#include "utils/xml_parser/xml_parser.h"
#include "game_handler/game_state_manager.h"
#include <iostream>
#include "game_book/creature.h"

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "path to book must be provided!" << std::endl;
			return 1;
	}

	//Creature * a =
	xml::Parser xmp;
	graphics::Window::visible_consiederation = 30;
	GameStateManager gsm(argv[1]);
	gsm.Launch();
	return 0;
}

