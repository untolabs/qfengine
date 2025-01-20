#ifndef CLIENT_OPENGL_GL_RMAIN_HH
#define CLIENT_OPENGL_GL_RMAIN_HH 1
#pragma once

struct DynamicLevelData;
struct StaticLevelData;
struct VideoMode;

namespace ref_opengl
{
void init(void);
void init_late(void);
} // namespace ref_opengl

namespace ref_opengl
{
void ref_init(const char *title, const VideoMode &vmode);
void ref_deinit(void);
void ref_prepare(void);
void ref_present(void);
} // namespace ref_opengl

namespace ref_opengl
{
void level_init(const StaticLevelData &data);
void level_deinit(void);
void level_render(const DynamicLevelData &data);
} // namespace ref_opengl

#endif /* CLIENT_OPENGL_GL_RMAIN_HH */
