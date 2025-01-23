#include "client/precompiled.hh"
#include "client/input.hh"

#include "core/config.hh"
#include "core/logging.hh"

#include "client/globals.hh"

IN_Bits input::bits = 0;

static unsigned int key_forward = SDLK_W;
static unsigned int key_back = SDLK_S;
static unsigned int key_left = SDLK_A;
static unsigned int key_right = SDLK_D;
static unsigned int key_jump = SDLK_SPACE;
static unsigned int key_crouch = SDLK_LCTRL;
static unsigned int key_sprint = SDLK_LSHIFT;
static unsigned int key_attack1 = SDLK_UNKNOWN;
static unsigned int key_attack2 = SDLK_UNKNOWN;
static unsigned int key_use = SDLK_E;

static unsigned int mb_attack1 = SDL_BUTTON_LEFT;
static unsigned int mb_attack2 = SDL_BUTTON_RIGHT;

static void update_bits(IN_Bits flag, bool set_flag)
{
    if(set_flag)
        input::bits |= flag;
    else input::bits &= ~flag;
}

static void on_keyboard_event(const SDL_KeyboardEvent &event)
{
    if(event.key == SDLK_UNKNOWN) {
        QF_warning("input: SDLK_UNKNOWN keycode");
        return;
    }

    if(event.key == key_forward) {
        update_bits(IN_FORWARD, event.down);
        return;
    }

    if(event.key == key_back) {
        update_bits(IN_BACK, event.down);
        return;
    }

    if(event.key == key_left) {
        update_bits(IN_LEFT, event.down);
        return;
    }

    if(event.key == key_right) {
        update_bits(IN_RIGHT, event.down);
        return;
    }

    if(event.key == key_jump) {
        update_bits(IN_JUMP, event.down);
        return;
    }

    if(event.key == key_crouch) {
        update_bits(IN_CROUCH, event.down);
        return;
    }

    if(event.key == key_sprint) {
        update_bits(IN_SPRINT, event.down);
        return;
    }

    if(event.key == key_attack1) {
        update_bits(IN_ATTACK1, event.down);
        return;
    }

    if(event.key == key_attack2) {
        update_bits(IN_ATTACK2, event.down);
        return;
    }

    if(event.key == key_use) {
        update_bits(IN_USE, event.down);
        return;
    }
}

static void on_mouse_button_event(const SDL_MouseButtonEvent &event)
{
    if(event.button == mb_attack1) {
        update_bits(IN_ATTACK1, event.down);
        return;
    }

    if(event.button == mb_attack2) {
        update_bits(IN_ATTACK2, event.down);
        return;
    }
}

void input::init(void)
{
    config::add("key.forward", key_forward);
    config::add("key.back", key_back);
    config::add("key.left", key_left);
    config::add("key.right", key_right);
    config::add("key.jump", key_jump);
    config::add("key.crouch", key_crouch);
    config::add("key.sprint", key_sprint);
    config::add("key.attack1", key_attack1);
    config::add("key.attack2", key_attack2);
    config::add("key.use", key_use);

    config::add("mouse.attack1", mb_attack1);
    config::add("mouse.attack2", mb_attack2);

    globals::dispatcher.sink<SDL_KeyboardEvent>().connect<&on_keyboard_event>();
    globals::dispatcher.sink<SDL_MouseButtonEvent>().connect<&on_mouse_button_event>();
}
