#include "shared/precompiled.hh"
#include "shared/content.hh"

#include "core/assert.hh"
#include "core/cmdline.hh"
#include "core/logging.hh"

#include "shared/const.hh"

void content::init(const char *argv_0)
{
    if(!PHYSFS_init(argv_0)) {
        const auto error = PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
        QF_throw("PhysFS_init: %s", error);
    }

    if(auto change_dir = cmdline::get("cdir")) {
        std::filesystem::current_path(change_dir);
    }

    auto working_dir = std::filesystem::current_path().string();

    if(!PHYSFS_mount(working_dir.c_str(), nullptr, true)) {
        const auto error = PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
        QF_throw("PHYSFS_mount: %s: %s", working_dir.c_str(), error);
    }

    if(auto game_dir = cmdline::get("game")) {
        if(!PHYSFS_setWriteDir(game_dir)) {
            const auto error = PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
            QF_throw("PHYSFS_setWriteDir: %s: %s", game_dir, error);
        }

        if(!PHYSFS_mount(game_dir, nullptr, true)) {
            const auto error = PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
            QF_throw("PHYSFS_mount: %s: %s", game_dir, error);
        }
    }

    if(!PHYSFS_mount(BASE_GAME_DIR, nullptr, true)) {
        const auto error = PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
        QF_throw("PHYSFS_mount: %s: %s", BASE_GAME_DIR, error);
    }
}

void content::deinit(void)
{
    if(!PHYSFS_deinit()) {
        const auto error = PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
        QF_throw("PHYSFS_deinit: %s", error);
    }
}
