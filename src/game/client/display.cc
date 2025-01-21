#include "client/precompiled.hh"
#include "client/display.hh"

#include "core/assert.hh"
#include "core/cmdline.hh"
#include "core/constexpr.hh"
#include "core/logging.hh"

static int base_width;
static int base_height;
static float base_rate;

static SDL_DisplayID chosen_display;
static SDL_DisplayMode **display_modes;
static int num_display_modes;

void display::init(void)
{
    if(auto mode_string = cmdline::get("vmode")) {
        std::sscanf(mode_string, "%dx%d:%f", &base_width, &base_height, &base_rate);
        base_rate = cxpr::clamp(base_rate, 30.0f, 300.0f);
        base_height = cxpr::max(16, base_height);
        base_width = cxpr::max(16, base_width);
    }
    else {
        base_width = 640;
        base_height = 480;
        base_rate = 60.0f;
    }
}

void display::init_late(void)
{
    int num_displays;
    auto displays = SDL_GetDisplays(&num_displays);
    QF_assert_msg(displays, SDL_GetError());

    int display_index;
    display_index = static_cast<int>(std::strtol(cmdline::get("display", "0"), nullptr, 10));
    display_index = cxpr::clamp(display_index, 0, (num_displays - 1));

    chosen_display = displays[display_index];
    QF_assert_debug(chosen_display);

    SDL_free(displays);

    QF_inform("display: display index: %d", display_index);
    QF_inform("display: using display: %s", SDL_GetDisplayName(chosen_display));

    display_modes = SDL_GetFullscreenDisplayModes(chosen_display, &num_display_modes);
    QF_assert_msg(display_modes, SDL_GetError);

    for(int i = 0; i < num_display_modes; ++i) {
        QF_verbose("display: mode %d: %dx%d:%.03f", i, display_modes[i]->w, display_modes[i]->h, display_modes[i]->refresh_rate);
    }
}

void display::deinit(void)
{
    SDL_free(display_modes);
}

const SDL_DisplayMode *display::current_mode(void)
{
    return SDL_GetCurrentDisplayMode(chosen_display);
}

const SDL_DisplayMode *display::find_mode(int width, int height, float rate)
{
    auto request_width = width ? width : base_width;
    auto request_height = height ? height : base_height;
    auto request_rate = rate ? rate : base_rate;

    int closest_index = 0;
    int closest_dx = INT_MAX;
    int closest_dy = INT_MAX;
    float closest_dr = FLT_MAX;

    for(int i = 0; i < num_display_modes; ++i) {
        auto dx = cxpr::abs(request_width - display_modes[i]->w);
        auto dy = cxpr::abs(request_height - display_modes[i]->h);
        auto dr = cxpr::abs(request_rate - display_modes[i]->refresh_rate);

        if((dx <= closest_dx) && (dy <= closest_dy) && (dr <= closest_dr)) {
            closest_index = i;
            closest_dx = dx;
            closest_dy = dy;
            closest_dr = dr;
            continue;
        }
    }

    return display_modes[closest_index];
}
