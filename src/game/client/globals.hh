#ifndef CLIENT_GLOBALS_HH
#define CLIENT_GLOBALS_HH 1
#pragma once

#include "shared/globals.hh"

namespace globals
{
extern SDL_Window *window;
extern float window_aspect;
extern int window_height;
extern int window_width;
} // namespace globals

namespace globals
{
extern float window_frametime;
extern float window_frametime_avg;
extern std::uint64_t window_frametime_us;
extern std::size_t window_framecount;
} // namespace globals

#endif /* CLIENT_GLOBALS_HH */
