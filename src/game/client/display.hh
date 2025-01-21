#ifndef CLIENT_DISPLAY_HH
#define CLIENT_DISPLAY_HH 1
#pragma once

constexpr static int AUTO_WIDTH = 0;
constexpr static int AUTO_HEIGHT = 0;
constexpr static float AUTO_RATE = 0.0f;

namespace display
{
void init(void);
void init_late(void);
void deinit(void);
} // namespace display

namespace display
{
const SDL_DisplayMode *current_mode(void);
const SDL_DisplayMode *find_mode(int width, int height, float rate);
} // namespace display

#endif /* CLIENT_DISPLAY_HH */
