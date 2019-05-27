#include "graphics/window_manager.h"
#include "graphics/textbox.h"
#include "graphics/menu.h"

size_t red_on_white = 1,
       magneta_on_blue = 3,
       white_on_red = 4,
       red_on_black = 5;

graphics::WindowManager wm;

void show_choice_screen(const std::string & text)
{
    auto & holla = wm.SelectScreen("holla");
    holla.Clear();

    auto & finito = holla.AddWindow<graphics::Textbox>(graphics::Window::WidthPercent(50),
                                     20,
                                     graphics::Window::WidthPercent(25), white_on_red);
    finito.AppendText(text, red_on_white);
    finito.NewLine();
    finito.AppendText("you'll be redirected to main screen after pushing any button", red_on_black);
    wm.Draw();    
    getch();
}

void main_screen()
{
    auto & main = wm.SelectScreen("main");


    auto & tb = main.AddWindow<graphics::Textbox>(40, 3, 3, magneta_on_blue);
    tb.AppendText("use UP and DOWN to scroll");
    tb.AppendText("astala vista, baby");
    tb.AppendText("hold Shift + -> or <- to move me around :):0000))");
    tb.Commit();

    auto & menu = main.AddWindow<graphics::Menu>(graphics::Window::WidthPercent(80),
                               main.LastAdded().LowestPoint() + 3,
                               graphics::Window::WidthPercent(10),
                                white_on_red, red_on_white, white_on_red, 5);
   
    menu.AppendText("CHOOSE STH.!");
    menu.NewLine();
    menu.AppendText("press <- or -> to select different options");
    menu.AppendText("press 'ENTER' to show your choice on another screen");
    menu.AppendText("press 'q' to quit", red_on_black);
    menu.AddOption("za");
    menu.AddOption("zel");
    menu.AddOption("aza zel azazel, barimel, actimel");
    menu.AddOption("forel");
    menu.AddOption("actimel");
    menu.AddOption("MALTHAEL his malibu on tu ru ru, halimizibi karum varum chenning tatum");

    menu.Commit();

    auto & group = main.AddWindow<graphics::Group<graphics::Textbox>>(graphics::Window::WidthPercent(50),
                                          menu.LowestPoint() + 3,
                                          5, red_on_white, 2, 5, 10);
    auto & gtb1 = group.EmplaceBack(white_on_red);
    auto & gtb2 = group.EmplaceBack(red_on_white);
    gtb1.AppendText("me and my friend on the right are bound into group. \
                     it means we both have the same height all the time, \
                     even though his text is much smaller");
    gtb2.AppendText("figaro?");

    wm.Draw();

    int ch;
    char info[30];
    while((ch = getch())!='q')
    {
        switch (ch)
        {
            case KEY_UP:
                wm.Move(graphics::Direction::Up);
                break;
            case KEY_DOWN:
                wm.Move(graphics::Direction::Down);
                break;
            case KEY_LEFT:
                menu--;
                break;
            case KEY_RIGHT:
                menu++;
                break;
            case KEY_SLEFT:
                tb.Move(1, -1);
                break;
            case KEY_SRIGHT:
                tb.Move(-1, 1);
                break;
            case 10:
                show_choice_screen(menu.GetChoiceText());
                wm.SelectScreen("main");
                break;
            default:
                continue;
        }
        sprintf(info, "coords are: y: %d x: %d", tb.HighestPoint(), tb.LeftPoint());
        tb.AlterText(tb.SizeLines() - 1, info);
        wm.Draw();
    }
}

int main()
{   

    init_pair(white_on_red, COLOR_WHITE, COLOR_RED);
    init_pair(red_on_white, COLOR_RED, COLOR_WHITE);
    init_pair(magneta_on_blue, COLOR_MAGENTA, COLOR_BLUE);
    init_pair(red_on_black, COLOR_RED, COLOR_BLACK);

    main_screen();
    
}
