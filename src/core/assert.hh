#ifndef CORE_ASSERT_HH
#define CORE_ASSERT_HH 1
#pragma once

#include "core/exception.hh"

/**
 * Triggers a crash if `condition` resolves to `false`
 * @param condition The condition to check for
 */
#define QF_assert(condition) if(!(condition)) QF_throw("Assertion failed:\n%s", #condition); else static_cast<void>(0)

/**
 * Triggers a crash if `condition` resolves to `false`
 * @param condition The condition to check for
 * @param message Message to print after the "assertion failed" line
 */
#define QF_assert_msg(condition, message) if(!(condition)) QF_throw("%s", (message)); else static_cast<void>(0)

#ifdef NDEBUG
#define QF_assert_debug(condition) static_cast<void>(condition)
#define QF_assert_msg_debug(condition, message) static_cast<void>(condition)
#endif /* NDEBUG */

#ifndef QF_assert_debug
/**
 * Triggers a crash if `condition` resolves to `false` but only for non-RELEASE builds
 * @param condition The condition to check for
 * @note This only works for non-RELEASE builds
 */
#define QF_assert_debug(condition) QF_assert(condition)
#endif /* QF_assert_debug */

#ifndef QF_assert_msg_debug
/**
 * Triggers a crash if `condition` resolves to `false` but only for non-RELEASE builds
 * @param condition The condition to check for
 * @param message Message to print after the "assertion failed" line
 * @note This only works for non-RELEASE builds
 */
#define QF_assert_msg_debug(condition, message) QF_assert_msg(condition, message)
#endif /* QF_assert_msg_debug */

#endif /* CORE_ASSERT_HH */
