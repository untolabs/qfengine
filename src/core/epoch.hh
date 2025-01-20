#ifndef CORE_EPOCH_HH
#define CORE_EPOCH_HH 1
#pragma once

namespace epoch
{
/**
 * Get UNIX seconds
 * @returns The amount of seconds passed
 * since 1970-01-01 00:00:00 local time
 */
std::uint64_t seconds(void);

/**
 * Get UNIX milliseconds
 * @returns The amount of milliseconds passed
 * since 1970-01-01 00:00:00.000 local time
 */
std::uint64_t milliseconds(void);

/**
 * Get UNIX microseconds
 * @returns The amount of microseconds passed
 * since 1970-01-01 00:00:00.000000 local time
 */
std::uint64_t microseconds(void);
} // namespace epoch

namespace epoch
{
/**
 * Get signed UNIX seconds
 * @returns The amount of seconds passed
 * since 1970-01-01 00:00:00 local time
 */
std::int64_t signed_seconds(void);

/**
 * Get signed UNIX milliseconds
 * @returns The amount of milliseconds passed
 * since 1970-01-01 00:00:00.000 local time
 */
std::int64_t signed_milliseconds(void);

/**
 * Get signed UNIX microseconds
 * @returns The amount of microseconds passed
 * since 1970-01-01 00:00:00.000000 local time
 */
std::int64_t signed_microseconds(void);
} // namespace epoch

#endif /* CORE_EPOCH_HH */
