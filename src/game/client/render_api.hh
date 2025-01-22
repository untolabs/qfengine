#ifndef CLIENT_RENDER_RENDER_API_HH
#define CLIENT_RENDER_RENDER_API_HH 1
#pragma once

enum RenderAPI {
    RenderAPI_Invalid,
    RenderAPI_OpenGL,
    RenderAPI_Vulkan,
};

class DynamicLevelData;
class StaticLevelData;

using PFN_render_video_init = void(*)(void);
using PFN_render_video_deinit = void(*)(void);
using PFN_render_video_prepare = void(*)(void);
using PFN_render_video_present = void(*)(void);

using PFN_render_level_init = void(*)(const StaticLevelData &data);
using PFN_render_level_deinit = void(*)(void);
using PFN_render_level_render = void(*)(const DynamicLevelData &data);

namespace render_api
{
extern RenderAPI current_api;
} // namespace render_api

namespace render_api
{
extern PFN_render_video_init video_init;
extern PFN_render_video_deinit video_deinit;
extern PFN_render_video_prepare video_prepare;
extern PFN_render_video_present video_present;
} // namespace render_api

namespace render_api
{
extern PFN_render_level_init level_init;
extern PFN_render_level_deinit level_deinit;
extern PFN_render_level_render level_render;
} // namespace render_api

namespace render_api
{
void init(void);
void init_late(void);
void deinit(void);
} // namespace render_api

namespace render_api
{
void reset(RenderAPI api);
} // namespace render_api

#endif /* CLIENT_RENDER_RENDER_API_HH */
