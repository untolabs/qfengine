#include "client/precompiled.hh"
#include "client/refresher.hh"

#include "core/assert.hh"
#include "core/cmdline.hh"
#include "core/constexpr.hh"
#include "core/feature.hh"
#include "core/logging.hh"

#include "client/opengl/ref_opengl.hh"
#include "client/globals.hh"

PFN_ref_init refresher::fn_ref_init = nullptr;
PFN_ref_deinit refresher::fn_ref_deinit = nullptr;
PFN_ref_prepare refresher::fn_ref_prepare = nullptr;
PFN_ref_present refresher::fn_ref_present = nullptr;
PFN_ref_level_init refresher::fn_level_init = nullptr;
PFN_ref_level_deinit refresher::fn_level_deinit = nullptr;
PFN_ref_level_render refresher::fn_level_render = nullptr;

void refresher::init(void)
{
    ref_opengl::init();

}

void refresher::init_late(void)
{
    ref_opengl::init_late();

    refresher::set(Ref_OpenGL);
}

void refresher::deinit(void)
{
    if(refresher::fn_ref_deinit) {
        // Allow the refresher to gracefully free up
        // resources it hogs before forced actions
        refresher::fn_ref_deinit();
    }

    if(globals::window) {
        QF_warning("refresher: refresher didn't close the window");
        SDL_DestroyWindow(globals::window);
    }

    globals::window = 0;
    globals::window_aspect = 0.0f;
    globals::window_height = 0;
    globals::window_width = 0;

    refresher::fn_ref_init = nullptr;
    refresher::fn_ref_deinit = nullptr;
    refresher::fn_ref_prepare = nullptr;
    refresher::fn_ref_present = nullptr;
    refresher::fn_level_init = nullptr;
    refresher::fn_level_deinit = nullptr;
    refresher::fn_level_render = nullptr;
}

void refresher::set(Ref_ID id)
{
    VideoMode vmode;
    vmode.fullscreen = cmdline::contains("fullscreen");
    vmode.height = std::atoi(cmdline::get("height", "480"));
    vmode.width = std::atoi(cmdline::get("width", "640"));

    vmode.height = cxpr::max(16, vmode.height);
    vmode.width = cxpr::max(16, vmode.width);

    if(globals::window) {
        vmode.fullscreen = !!(SDL_GetWindowFlags(globals::window) & SDL_WINDOW_FULLSCREEN);
        vmode.height = cxpr::max(16, globals::window_height);
        vmode.width = cxpr::max(16, globals::window_width);
    }

    if(refresher::fn_ref_deinit) {
        // Allow the refresher to gracefully free up
        // resources it hogs before forced actions
        refresher::fn_ref_deinit();
    }

    if(globals::window) {
        QF_warning("refresher: refresher didn't close the window");
        SDL_DestroyWindow(globals::window);
    }

    globals::window = 0;
    globals::window_aspect = 0.0f;
    globals::window_height = 0;
    globals::window_width = 0;

    refresher::fn_ref_init = nullptr;
    refresher::fn_ref_deinit = nullptr;
    refresher::fn_ref_prepare = nullptr;
    refresher::fn_ref_present = nullptr;
    refresher::fn_level_init = nullptr;
    refresher::fn_level_deinit = nullptr;
    refresher::fn_level_render = nullptr;

    if(id == Ref_OpenGL) {
        refresher::fn_ref_init = &ref_opengl::ref_init;
        refresher::fn_ref_deinit = &ref_opengl::ref_deinit;
        refresher::fn_ref_prepare = &ref_opengl::ref_prepare;
        refresher::fn_ref_present = &ref_opengl::ref_present;
        refresher::fn_level_init = &ref_opengl::level_init;
        refresher::fn_level_deinit = &ref_opengl::level_deinit;
        refresher::fn_level_render = &ref_opengl::level_render;
    }

    QF_assert_msg(refresher::fn_ref_init, "Unknown or unsupported refresher");

    bool refresher_complete = true;
    refresher_complete = refresher_complete && refresher::fn_ref_deinit;
    refresher_complete = refresher_complete && refresher::fn_ref_prepare;
    refresher_complete = refresher_complete && refresher::fn_ref_present;
    refresher_complete = refresher_complete && refresher::fn_level_init;
    refresher_complete = refresher_complete && refresher::fn_level_deinit;
    refresher_complete = refresher_complete && refresher::fn_level_render;

    QF_assert_msg(refresher_complete, "Refresher implementation is incomplete");

    refresher::fn_ref_init("QFengine", vmode);

    QF_assert_msg(globals::window, "Refresher failed to open a window");
}
