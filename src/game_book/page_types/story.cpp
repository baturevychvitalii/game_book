#include "story.h"
#include "../../utils/graphics/textbox.h"
#include "../../game_handler/colors.h"

Story::Story(const xml::Tag & root, GameStateManager * g)
    : Page(root, g)
{
    auto & body = AddWindow<graphics::Textbox>(
        "body",
        graphics::max_x - 4,
        TopWindow()->LowestPoint() + 4,
        2,
        page_story_body_color
    ).AppendText(root.Child("body").Text());

    Commit();
    
    BotWindow()->MoveTo(body.LowestPoint() + 2, BotWindow()->LeftPoint());
}
