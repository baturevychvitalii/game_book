#include "page.h"

Page::Page(const std::string & file, const xml::Tag & root, Creature & pleya)
    : filename(file), player(pleya), 
    screen(wm.SelectScreen("page"))
{
    crossroads.reserve(5);
    try
    {
        for (const xml::Tag & tag : root.Child("crossroad").GetVector("path"))
        {
            crossroads.emplace_back(tag.Prop("to"), tag.Text());
        }
    }
    catch(const xml::XmlException & e)
    {
        // if some crossroads were added - incorrect format in current tag
        // else - end game because no further path
        if (!crossroads.empty())
            throw e;
    } 

    screen.AddWindow<graphics::Textbox>(
        "header",
        graphics::Window::XPercent(100),
        0,
        0,
        hacker
    ).AppendText(root.Child("header").Text());

    screen.Commit();
}

void Page::Bookmark() const
{
    auto root = xml::Tag("save");
    root.AddChild(Serialize());
    root.AddChild(player.Serialize());
    auto doc = xml::Parser::NewDoc(save_path, root);
    doc.Save();
}

Page::~Page()
{
    screen.Clear();
}

std::string Page::GetNextPage() const
{
    if (crossroads.empty())
        throw "shouldn't have come to this point, Play() should have returned 1";
        
    auto & screen = wm.SelectScreen("crossroad");
    auto & menu = screen.AddWindow<graphics::Menu>(
        "menu",
        graphics::Window::XPercent(90),
        0,
        graphics::Window::XPercent(5),
        magneta_on_black,
        hacker,
        cyan_on_black,
        2
    );
    menu.AppendText("Where now, Lorry?");
    for (auto & pair: crossroads)
        menu.AddOption(pair.second);

    size_t choice = GetMenuSelection(menu);
    screen.Clear();
    return crossroads[choice].first;
}

xml::Tag Page::Serialize() const
{
    auto t = xml::Tag("page");
    t.AddText(filename);
    return t;
}

size_t Page::PauseMenu() const
{
    return GetMenuSelection(
        wm.SelectScreen("pause").
        GetWindow<graphics::Menu>("pause menu")
    );
}

int Page::DefaultPageHandling()
{
    wm.Draw();
    auto & footer = screen.GetWindow("footer");
    auto & header = screen.GetWindow("header");

    int input;
    while (true) // not pause exit
    {
        input = getch();
        switch (input)
        {
            case KEY_UP:
                if (footer.LowestPoint() > graphics::Window::max_y)
                    wm.Move(graphics::Direction::Up, 3);
                break;
            case KEY_DOWN:
                if (header.HighestPoint() < 0)
                    wm.Move(graphics::Direction::Down, 3);
                break;
            case 'p':
                input = PauseMenu();
                if (input == 0) // continue
                {
                }
                else if (input == 1) // save
                {
                    try
                    {
                        Bookmark();
                    }
                    catch(const std::exception & e)
                    {
                        RaiseErrorWindow(e);
                    }
                }
                else if (input == 2) // controls
                {
                    wm.SelectScreen("controls");
                    wm.Draw();
                    getch();
                }
                else if (input == 3) // to main menu
                {
                    return -1;
                }
                else
                {
                    throw "pause menu returned unsupported value";
                }

                wm.SelectScreen(screen);
                break;
            default: // unknown inputs are passed to caller and handled by them
                return input;
        }
        
        wm.Draw();
    }
    
}

