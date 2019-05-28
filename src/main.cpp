#include "utils/graphics/menu.h"
#include "utils/graphics/window_manager.h"

#include "utils/xml_parser/xml_parser.h"

static const char * first_page = "book/story_example.xml";
static const char * save_file = "save.xml";

size_t red_on_white = 1,
       magneta_on_blue = 3,
       white_on_red = 4,
       red_on_black = 5;

size_t error_color = red_on_black;
       


graphics::WindowManager wm;
xml_parser::Parser xmp;

void InitColors()
{
    init_pair(white_on_red, COLOR_WHITE, COLOR_RED);
    init_pair(red_on_white, COLOR_RED, COLOR_WHITE);
    init_pair(magneta_on_blue, COLOR_MAGENTA, COLOR_BLUE);
    init_pair(red_on_black, COLOR_RED, COLOR_BLACK);
}

void RaiseErrorWindow(const std::exception & e)
{
    auto & err = wm.SelectScreen("error");
    err.AddWindow<graphics::Textbox>(graphics::Window::XPercent(50),
                                    graphics::Window::YPercent(10), 
                                    graphics::Window::XPercent(25),
                                    error_color).
                                    AppendText(e.what());
    wm.Draw();
    wm.RemoveScreen("error");
    getch();
}

void PlayPage(const std::string & filename)
{

}

bool ProcessSelection(size_t choice)
{
    if (choice == 0) // New
    {
        PlayPage(first_page);
    }
    else if (choice == 1) // Load
    {
        try
        {
            auto save_doc = xmp.GetDoc(save_file);
            auto root = save_doc.Root();

        }
        catch(const std::exception & e)
        {
            RaiseErrorWindow(e);
        }
    }
    else if (choice == 2) // Quit
    {
        return true;
    }
    else
    {
        throw std::invalid_argument("impossible choice");
    }
    
    return false;
}

void MainScreen()
{
    auto & main = wm.SelectScreen("main");

    auto & menu = main.AddWindow<graphics::Menu>(graphics::Window::XPercent(50),
                               4,
                               graphics::Window::XPercent(25),
                                white_on_red, red_on_white, white_on_red, 1);
   
    menu.AppendText("Story of Lory");
    menu.NewLine();
    menu.AppendText("<  or  > to select different options");
    menu.AppendText("^  or  v to scroll");
    menu.AddOption("New");
    menu.AddOption("Load");
    menu.AddOption("Quit");
    wm.Draw();

    bool quit = false;
    int input;
    while(!quit)
    {
        input = getch();
        switch (input)
        {
            case KEY_UP:
                if (menu.HighestPoint() > 0)
                    wm.Move(graphics::Direction::Up);
                break;
            case KEY_DOWN:
                if (menu.LowestPoint() < graphics::Window::max_y)
                    wm.Move(graphics::Direction::Down);
                break;
            case KEY_LEFT:
                menu--;
                break;
            case KEY_RIGHT:
                menu++;
                break;
            case 10:
                quit = ProcessSelection(menu.GetChoice());
                wm.SelectScreen("main");
                break;
            default:
                continue;
        }
        wm.Draw();
    }
}

int main()
{
    InitColors();
    MainScreen();
}
