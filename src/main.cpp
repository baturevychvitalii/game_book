#include "utils/xml_parser/xml_parser.h"
#include "game_handler/game_state_manager.h"



int main()
{
    xml::Parser xmp;
    graphics::Window::visible_consiederation = 30;
    GameStateManager gsm;
    gsm.Launch();   
}

