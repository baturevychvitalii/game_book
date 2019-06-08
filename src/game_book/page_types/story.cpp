#include "story.h"
#include "../../utils/graphics/textbox.h"
#include "../../game_handler/colors.h"

Story::Story(const xml::Tag & root, GameStateManager * g)
    : Page(root, g)
{
    auto & body = AddWindow<graphics::Textbox>(
        "body",
        graphics::max_x,
        TopWindow()->LowestPoint(),
        0,
        page_story_body_color
    ).AppendText(root.Child("body").Text());

    Commit();
    
    BotWindow()->MoveTo(body.LowestPoint(), BotWindow()->LeftPoint());
	BotWindow()->ProlongueToBottom();
}

bool Story::Reacted(int input)
{
	if (StandardMenuHandlerReacted(static_cast<graphics::menu_base *>(BotWindow()), input))
		return true;

	return Page::Reacted(input);
}
