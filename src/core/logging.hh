#ifndef CORE_LOGGING_HH
#define CORE_LOGGING_HH 1
#pragma once

/**
 * Message priority level for logging functions
 */
enum QF_LogLevel : unsigned int {
    QF_SILENT   = 0x0000, ///< Special constant for disabling logging altogether
    QF_VERBOSE  = 0x0001, ///< Messages normally disabled on RELEASE builds
    QF_INFORM   = 0x0002, ///< General purpose logging level
    QF_NOTICE   = 0x0003, ///< There are reasons for the user to be concerned
    QF_WARNING  = 0x0004, ///< Something bad is going on so user be advised
    QF_ERROR    = 0x0005, ///< Something bad happened but we can still recover
    QF_EMERG    = 0x0006, ///< Something bad happened and we're going to bail
};

#ifdef NDEBUG
constexpr static QF_LogLevel DEFAULT_LOG_LEVEL = QF_INFORM;
#else
constexpr static QF_LogLevel DEFAULT_LOG_LEVEL = QF_VERBOSE;
#endif

/**
 * A message callback function pointer
 * @param level Message priority associated with the message
 * @param string Zero-terminated message string
 * @param size Length of the message
 * @note Whenever this function is called, it is guaranteed to be wrapped around
 * a mutex and is guaranteed to have passed all the internal log level checks
 */
using QF_LogFunction = void(*)(QF_LogLevel level, const char *string, std::size_t size);

namespace logging
{
/**
 * The default logging callback
 * @param level Message priority associated with the message
 * @param string Zero-terminated message string
 * @param size Length of the message
 * @warning There are no internal thread-safety checks
 */
void default_callback(QF_LogLevel level, const char *string, std::size_t size);

/**
 * Set the message callback
 * @param callback Message callback
 */
void set_callback(QF_LogFunction callback);

/**
 * Set the log level
 * @param level Log level
 */
void set_level(QF_LogLevel level);

/**
 * Sets up the logger with a level that may
 * have been passed into the command line;
 */
void init_from_cmdline(void);
} // namespace logging

namespace logging
{
/**
 * Print a message
 * @param level Log level
 * @param format Format string in sprintf style
 * @see cppreference for [fprintf](https://en.cppreference.com/w/c/io/fprintf)
 */
void printf(QF_LogLevel level, const char *format, ...);

/**
 * Print a message
 * @param level Log level
 * @param format Format string in sprintf style
 * @param va Variadic argument list
 * @see cppreference for [vfprintf](https://en.cppreference.com/w/c/io/vfprintf)
 */
void vprintf(QF_LogLevel level, const char *format, std::va_list va);
} // namespace logging

/**
 * Print a formatted message with `QF_VERBOSE` level
 * @param format Format string in sprintf style
 */
#define QF_verbose(format, ...) logging::printf(QF_VERBOSE, (format), ##__VA_ARGS__)

/**
 * Print a formatted message with `QF_INFORM` level
 * @param format Format string in sprintf style
 */
#define QF_inform(format, ...) logging::printf(QF_INFORM, (format), ##__VA_ARGS__)

/**
 * Print a formatted message with `QF_NOTICE` level
 * @param format Format string in sprintf style
 */
#define QF_notice(format, ...) logging::printf(QF_NOTICE, (format), ##__VA_ARGS__)

/**
 * Print a formatted message with `QF_WARNING` level
 * @param format Format string in sprintf style
 */
#define QF_warning(format, ...) logging::printf(QF_WARNING, (format), ##__VA_ARGS__)

/**
 * Print a formatted message with `QF_ERROR` level
 * @param format Format string in sprintf style
 */
#define QF_error(format, ...) logging::printf(QF_ERROR, (format), ##__VA_ARGS__)

/**
 * Print a formatted message with `QF_EMERG` level
 * @param format Format string in sprintf style
 */
#define QF_emerg(format, ...) logging::printf(QF_EMERG, (format), ##__VA_ARGS__)

/**
 * Print a formatted message with `QF_VERBOSE` level
 * @param format Format string in sprintf style
 * @param va Variadic argument list
 */
#define QF_va_verbose(format, va) logging::vprintf(QF_VERBOSE, (format), (va))

/**
 * Print a formatted message with `QF_INFORM` level
 * @param format Format string in sprintf style
 * @param va Variadic argument list
 */
#define QF_va_inform(format, va) logging::vprintf(QF_INFORM, (format), (va))

/**
 * Print a formatted message with `QF_NOTICE` level
 * @param format Format string in sprintf style
 * @param va Variadic argument list
 */
#define QF_va_notice(format, va) logging::vprintf(QF_NOTICE, (format), (va))

/**
 * Print a formatted message with `QF_WARNING` level
 * @param format Format string in sprintf style
 * @param va Variadic argument list
 */
#define QF_va_warning(format, va) logging::vprintf(QF_WARNING, (format), (va))

/**
 * Print a formatted message with `QF_ERROR` level
 * @param format Format string in sprintf style
 * @param va Variadic argument list
 */
#define QF_va_error(format, va) logging::vprintf(QF_ERROR, (format), (va))

/**
 * Print a formatted message with `QF_EMERG` level
 * @param format Format string in sprintf style
 * @param va Variadic argument list
 */
#define QF_va_emerg(format, va) logging::vprintf(QF_EMERG, (format), (va))

#endif /* CORE_LOGGING_HH */
