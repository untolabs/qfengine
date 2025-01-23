#ifndef SHARED_INPUT_HH
#define SHARED_INPUT_HH 1
#pragma once

using IN_Bits = std::uint16_t;
constexpr static IN_Bits IN_FORWARD = 0x0001; // Default: W; move forward
constexpr static IN_Bits IN_BACK    = 0x0002; // Default: S; move backwards
constexpr static IN_Bits IN_LEFT    = 0x0004; // Default: A; strafe left
constexpr static IN_Bits IN_RIGHT   = 0x0008; // Default: D; strafe right
constexpr static IN_Bits IN_JUMP    = 0x0010; // Default: SPACE; jump, fly or swim up
constexpr static IN_Bits IN_CROUCH  = 0x0020; // Default: LCTRL; crouch or fly down
constexpr static IN_Bits IN_SPRINT  = 0x0040; // Default: SHIFT; sprint or walk
constexpr static IN_Bits IN_ATTACK1 = 0x0080; // Default: MOUSE1; primary weapon attack
constexpr static IN_Bits IN_ATTACK2 = 0x0100; // Default: MOUSE2; secondary weapon attack
constexpr static IN_Bits IN_USE     = 0x0200; // Default: E; interact with something

struct ClientCommand final {
    glm::fvec3 wishdir;
    glm::fvec3 angles;
    IN_Bits keys;
};

#endif /* SHARED_INPUT_HH */
