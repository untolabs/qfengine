#include "client/precompiled.hh"
#include "client/render_api.hh"

#include "core/assert.hh"
#include "core/cmdline.hh"
#include "core/constexpr.hh"
#include "core/feature.hh"
#include "core/logging.hh"

#include "shared/const.hh"

#include "client/opengl/opengl.hh"
#include "client/display.hh"
#include "client/globals.hh"

RenderAPI render_api::current_api = RenderAPI_Invalid;

PFN_render_video_init render_api::video_init = nullptr;
PFN_render_video_deinit render_api::video_deinit = nullptr;
PFN_render_video_prepare render_api::video_prepare = nullptr;
PFN_render_video_present render_api::video_present = nullptr;

PFN_render_level_init render_api::level_init = nullptr;
PFN_render_level_deinit render_api::level_deinit = nullptr;
PFN_render_level_render render_api::level_render = nullptr;

void render_api::init(void)
{
    opengl::init();

}

void render_api::init_late(void)
{
    opengl::init_late();

    render_api::reset(RenderAPI_OpenGL);
}

void render_api::deinit(void)
{
    if(render_api::video_deinit) {
        // Allow the rendering API to gravefully free
        // up all the resources it hogs before we die
        render_api::video_deinit();
    }

    if(globals::window) {
        QF_warning("render_api: render_api didn't close the window");
        SDL_DestroyWindow(globals::window);
    }

    globals::window = 0;
    globals::window_aspect = 0.0f;
    globals::window_height = 0;
    globals::window_width = 0;

    render_api::video_init = nullptr;
    render_api::video_deinit = nullptr;
    render_api::video_prepare = nullptr;
    render_api::video_present = nullptr;

    render_api::level_init = nullptr;
    render_api::level_deinit = nullptr;
    render_api::level_render = nullptr;
}

void render_api::reset(RenderAPI api)
{
    const SDL_DisplayMode *mode;

    if(globals::window) {
        // Re-use the same display mode
        // as we're currently using
        mode = display::current_mode();
    }
    else {
        // Figure out a new video mode;
        // FIXME: pass these into render_api::reset as well?
        mode = display::find_mode(AUTO_WIDTH, AUTO_HEIGHT, AUTO_RATE);
    }

    QF_inform("render_api: display mode: %dx%d:%.03f", mode->w, mode->h, mode->refresh_rate);

    if(render_api::video_deinit) {
        // Allow the renderer to gracefully free up
        // resources it hogs before forced actions
        render_api::video_deinit();
    }

    if(globals::window) {
        QF_warning("render_api: renderer didn't close the window");
        SDL_DestroyWindow(globals::window);
    }

    globals::window = 0;
    globals::window_aspect = 0.0f;
    globals::window_height = 0;
    globals::window_width = 0;

    render_api::current_api = RenderAPI_Invalid;

    render_api::video_init = nullptr;
    render_api::video_deinit = nullptr;
    render_api::video_prepare = nullptr;
    render_api::video_present = nullptr;

    render_api::level_init = nullptr;
    render_api::level_deinit = nullptr;
    render_api::level_render = nullptr;

    if(api == RenderAPI_OpenGL) {
        render_api::video_init = &opengl::video_init;
        render_api::video_deinit = &opengl::video_deinit;
        render_api::video_prepare = &opengl::video_prepare;
        render_api::video_present = &opengl::video_present;

        render_api::level_init = &opengl::level_init;
        render_api::level_deinit = &opengl::level_deinit;
        render_api::level_render = &opengl::level_render;
    }

    QF_assert_msg(render_api::video_init, "Unknown or unsupported renderer");

    bool render_api_complete = true;
    render_api_complete = render_api_complete && render_api::video_deinit;
    render_api_complete = render_api_complete && render_api::video_prepare;
    render_api_complete = render_api_complete && render_api::video_present;
    render_api_complete = render_api_complete && render_api::level_init;
    render_api_complete = render_api_complete && render_api::level_deinit;
    render_api_complete = render_api_complete && render_api::level_render;

    QF_assert_msg(render_api_complete, "Renderer implementation is incomplete");

    render_api::video_init(CLIENT_TITLE);

    QF_assert_msg(globals::window, "Renderer failed to open a window");

    if(cmdline::contains("fullscreen") && !cmdline::contains("windowed")) {
        SDL_SetWindowFullscreenMode(globals::window, mode);
        SDL_SetWindowFullscreen(globals::window, true);
    }
    else {
        SDL_SetWindowSize(globals::window, mode->w, mode->h);
        SDL_SetWindowFullscreen(globals::window, false);
    }

    render_api::current_api = api;
}
