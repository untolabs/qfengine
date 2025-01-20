#include "client/precompiled.hh"
#include "client/globals.hh"

SDL_Window *globals::window = nullptr;
float globals::window_aspect;
int globals::window_height;
int globals::window_width;

float globals::window_frametime;
float globals::window_frametime_avg;
std::uint64_t globals::window_frametime_us;
std::size_t globals::window_framecount;
