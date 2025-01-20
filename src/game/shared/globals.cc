#include "shared/precompiled.hh"
#include "shared/globals.hh"

float globals::fixed_frametime;
float globals::fixed_frametime_avg;
std::uint64_t globals::fixed_frametime_us;
std::size_t globals::fixed_framecount;

std::uint64_t globals::curtime;

entt::dispatcher globals::dispatcher;
entt::registry globals::registry;
