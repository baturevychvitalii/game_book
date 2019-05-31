#include "story.h"

Story::Story(const xml::Tag & root, Game * g)
    : Page(root, g)
{
    screen.AddWindow<graphics::Textbox>(
        "footer",
        graphics::max_x - 4,
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
        if (unique_option == 10)
            break;
    }
    if (unique_option < 0 || crossroads.empty())
        return false;

    return true;
}
