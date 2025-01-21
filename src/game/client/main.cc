#include "client/precompiled.hh"

#include "core/assert.hh"
#include "core/cmdline.hh"
#include "core/constexpr.hh"
#include "core/crc64.hh"
#include "core/epoch.hh"
#include "core/logging.hh"

#include "client/display.hh"
#include "client/game.hh"
#include "client/globals.hh"
#include "client/render_api.hh"

static bool poll_events(void)
{
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_EVENT_QUIT) {
            // The user requested the application
            // to terminate; returning false terminates
            // the main loop in wrapped_main function
            return false;
        }

        if(event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) {
            QF_emerg("client: SDLK_ESCAPE has been pressed");
            QF_throw("client: SDLK_ESCAPE throw hack");
        }

        switch(event.type) {
        case SDL_EVENT_KEY_DOWN:
            globals::dispatcher.trigger(event.key);
            break;
        case SDL_EVENT_KEY_UP:
            globals::dispatcher.trigger(event.key);
            break;
        case SDL_EVENT_MOUSE_MOTION:
            globals::dispatcher.trigger(event.motion);
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            globals::dispatcher.trigger(event.button);
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            globals::dispatcher.trigger(event.button);
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            globals::dispatcher.trigger(event.wheel);
            break;
        }
    }

    return true;
}

static void wrapped_main(int argc, char **argv)
{
    cmdline::init(argc, argv);

    logging::init_from_cmdline();

    display::init();

    render_api::init();

    client_game::init();

    globals::fixed_frametime = FLT_MAX;
    globals::fixed_frametime_avg = FLT_MAX;
    globals::fixed_frametime_us = UINT64_MAX;
    globals::fixed_framecount = 0;

    globals::window_frametime = 0.0f;
    globals::window_frametime_avg = 0.0f;
    globals::window_frametime_us = UINT64_C(0);
    globals::window_framecount = 0;

    globals::curtime = epoch::microseconds();

    display::init_late();

    render_api::init_late();

    client_game::init_late();

    std::uint64_t last_curtime = globals::curtime;

    while(poll_events()) {
        globals::curtime = epoch::microseconds();
        globals::window_frametime_us = globals::curtime - last_curtime;
        globals::window_frametime = static_cast<float>(globals::window_frametime_us) / 1000000.0f;

        globals::window_frametime_avg += globals::window_frametime;
        globals::window_frametime_avg *= 0.5f;

        SDL_GetWindowSizeInPixels(globals::window, &globals::window_width, &globals::window_height);

        auto size_max = cxpr::max<float>(globals::window_width, globals::window_height);
        auto size_min = cxpr::min<float>(globals::window_width, globals::window_height);
        globals::window_aspect = size_max / size_min;

        client_game::window_update();

        render_api::video_prepare();

        client_game::window_update_late();

        render_api::video_present();
    }

    client_game::deinit();

    render_api::deinit();
}

int main(int argc, char **argv)
{
    try {
        QF_assert(SDL_InitSubSystem(SDL_INIT_AUDIO));
        QF_assert(SDL_InitSubSystem(SDL_INIT_VIDEO));
        QF_assert(SDL_InitSubSystem(SDL_INIT_EVENTS));

        wrapped_main(argc, argv);

        SDL_QuitSubSystem(SDL_INIT_EVENTS);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);

        SDL_Quit();

        return EXIT_SUCCESS;
    }
    catch(const std::exception &exception) {
        QF_emerg("engine error: %s", exception.what());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "QFengine Error", exception.what(), nullptr);
        SDL_TriggerBreakpoint();
        std::terminate();
    }

    return EXIT_FAILURE;
}
