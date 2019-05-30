    auto & pause = wm.AddScreen("pause");

    auto & menu = pause.AddWindow<graphics::Menu>(
        "pause menu",
        graphics::Window::XPercent(50),
        4,
        graphics::Window::XPercent(25),
        white_on_red, red_on_white, white_on_red, 1
    );

    menu.AppendText("Pause");
    pause_continue = menu.AddOption("Continue");
    pause_save = menu.AddOption("Save");
    pause_controls = menu.AddOption("Controls");
    pause_quit = menu.AddOption("Quit to main menu (unsaved progress will be lost FOREVER!!)");
}
