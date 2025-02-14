#ifndef CLIENT_GAME_HH
#define CLIENT_GAME_HH 1
#pragma once

namespace client_game
{
void init(void);
void init_late(void);
void deinit(void);
} // namespace client_game

namespace client_game
{
void fixed_update(void);
void fixed_update_late(void);
void window_update(void);
void window_update_late(void);
} // namespace client_game

namespace client_game
{
void layout_imgui(void);
} // namespace client_game

#endif /* CLIENT_GAME_HH */
