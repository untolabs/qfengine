#ifndef CLIENT_OPENGL_OPENGL_HH
#define CLIENT_OPENGL_OPENGL_HH 1
#pragma once

class DynamicLevelData;
class StaticLevelData;

namespace opengl
{
void init(void);
void init_late(void);
} // namespace opengl

namespace opengl
{
void video_init(void);
void video_deinit(void);
void video_prepare(void);
void video_present(void);
} // namespace opengl

namespace opengl
{
void level_init(const StaticLevelData &data);
void level_deinit(void);
void level_render(const DynamicLevelData &data);
} // namespace opengl

#endif /* CLIENT_OPENGL_OPENGL_HH */
