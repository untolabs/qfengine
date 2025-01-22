#include "shared/precompiled.hh"
#include "shared/game.hh"

#include "core/config.hh"

char shared_game::window_title[64];
char shared_game::mainmenu_title[64];

void shared_game::init(void)
{
    config::add("game.window_title", shared_game::window_title, sizeof(shared_game::window_title), FCONFIG_NO_SAVE);
    config::add("game.mainmenu_title", shared_game::mainmenu_title, sizeof(shared_game::mainmenu_title), FCONFIG_NO_SAVE);
}
