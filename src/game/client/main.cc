#include "client/precompiled.hh"

#include "core/assert.hh"
#include "core/cmdline.hh"
#include "core/crc64.hh"
#include "core/epoch.hh"
#include "core/logging.hh"

static void wrapped_main(int argc, char **argv)
{
    std::srand(static_cast<unsigned int>(time(nullptr)));
    const auto random_value = std::rand();

    QF_inform("Hello world!");
    QF_inform("Random value: %d", random_value);
    QF_inform("Supposedly forty two: %d", 42);

    auto qwerty = cmdline::get("qwerty");
    QF_inform("CRC of int %d: %" PRIu64, crc64::get(&random_value, sizeof(int)));
    QF_inform("Argument qwerty: %s", qwerty ? qwerty : "NULL");

    QF_assert_msg(random_value == 42, "Random value is not 42");
}

int main(int argc, char **argv)
{
    try {
        cmdline::init(argc, argv);

        QF_assert(SDL_InitSubSystem(SDL_INIT_AUDIO));
        QF_assert(SDL_InitSubSystem(SDL_INIT_VIDEO));
        QF_assert(SDL_InitSubSystem(SDL_INIT_EVENTS));

        wrapped_main(argc, argv);

        SDL_QuitSubSystem(SDL_INIT_EVENTS);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);

        SDL_Quit();

        return EXIT_SUCCESS;
    }
    catch(const std::exception &exception) {
        QF_emerg("engine error: %s", exception.what());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "QFengine Error", exception.what(), nullptr);
        SDL_TriggerBreakpoint();
        std::terminate();
    }

    return EXIT_FAILURE;
}
