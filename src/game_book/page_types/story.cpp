#include "story.h"

Story::Story(const std::string & filename, const xml::Tag & root, Creature & pleya)
    : Page(filename, root, pleya)
{
    screen.AddWindow<graphics::Textbox>(
        "footer",
        graphics::Window::max_x - 4,
        screen.GetWindow("header").LowestPoint() + 4,
        2,
        white_on_red
    ).AppendText(root.Child("body").Text());
}

bool Story::Play()
{
    wm.SelectScreen(screen);
    int unique_option;
    while ((unique_option = DefaultPageHandling()) >= 0)
    {
        
    }
}
