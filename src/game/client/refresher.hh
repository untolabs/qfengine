#ifndef CLIENT_RENDER_REFRESHER_HH
#define CLIENT_RENDER_REFRESHER_HH 1
#pragma once

#include "client/video_mode.hh"

enum Ref_ID {
    Ref_OpenGL,
    Ref_Vulkan,
};

struct DynamicLevelData;
struct StaticLevelData;

using PFN_ref_init = void(*)(const char *title, const VideoMode &vmode);
using PFN_ref_deinit = void(*)(void);
using PFN_ref_prepare = void(*)(void);
using PFN_ref_present = void(*)(void);

using PFN_ref_level_init = void(*)(const StaticLevelData &data);
using PFN_ref_level_deinit = void(*)(void);
using PFN_ref_level_render = void(*)(const DynamicLevelData &data);

namespace refresher
{
extern PFN_ref_init fn_ref_init;
extern PFN_ref_deinit fn_ref_deinit;
extern PFN_ref_prepare fn_ref_prepare;
extern PFN_ref_present fn_ref_present;
extern PFN_ref_level_init fn_level_init;
extern PFN_ref_level_deinit fn_level_deinit;
extern PFN_ref_level_render fn_level_render;
} // namespace refresher

namespace refresher
{
void init(void);
void init_late(void);
void deinit(void);
} // namespace refresher

namespace refresher
{
void set(Ref_ID id);
} // namespace refresher

#endif /* CLIENT_RENDER_REFRESHER_HH */
