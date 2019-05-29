#include "game.h"
#include "graphics_common.h"
#include "page_types/story.h"

Game::Game()
{
    InitColors();
    CreateMainMenu();
    CreatePauseMenu();
    CreateControlsWindow();
    CreateAuthorWindow();
}

size_t Game::MainMenu() const
{
    return GetMenuSelection(
        wm.SelectScreen("main").
        GetWindow<graphics::Menu>("main menu")
    );
}

std::unique_ptr<Page> Game::GetPage(const std::string & filename)
{
    auto doc = xmp.GetDoc(filename);
    auto root = doc.Root();
    if (root.Name() != "page")
        throw xml::XmlException("not a page file");

    std::string type = root.Prop("type");
    
    if (type == "story")
    {
        return std::make_unique<Story>(filename, root, player);
    }
    else
    {
        throw std::invalid_argument("file is not in correct format. Page must have a type");
    }
}

void Game::Play(std::string page_path)
{
    std::unique_ptr<Page> curr_page = GetPage(page_path);
    while (curr_page->Play())
    {
        page_path = curr_page->GetNextPage();
        curr_page = GetPage(page_path);
    }
}

void Game::StartFromMainMenu()
{
    size_t option = 0;
    std::string page_path;
    while (option != 4)
    {
        option = MainMenu();

        if (option == 0)
        {
            player = std::make_unique<Creature>();
            Play(first_page);
        }
        else if (option == 1)
        {
            try
            {
                Play(Load());
            }
            catch(const xml::XmlException & e)
            {
                RaiseErrorWindow(e);
            }
        }
        else if (option == 2)
        {
            wm.SelectScreen("controls");
            wm.Draw();
            getch();
        }
        else if (option == 3)
        {
            wm.SelectScreen("author");
            wm.Draw();
            getch;
        }
        else if (option == 4)
        {
        }
        else
        {
            throw graphics::GraphicsException("menu returned unexisting option");
        }
    } 
}
