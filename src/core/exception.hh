#ifndef CORE_EXCEPTION_HH
#define CORE_EXCEPTION_HH 1
#pragma once

/**
 * An `std::exception` implementation with the message
 * string that is produced from an sprintf-like function
 */
class QF_Exception final : public std::exception {
public:
    explicit QF_Exception(void) noexcept = default;
    virtual ~QF_Exception(void) noexcept = default;
    virtual const char *what(void) const noexcept override;

private:
    char buffer[4096];

public:
    /**
     * Creates a new QF_Exception
     * @param format Format string in sprintf style
     * @see cppreference for [fprintf](https://en.cppreference.com/w/c/io/fprintf)
     * @returns A new QF_Exception object 
     */
    static QF_Exception create(const char *format, ...) noexcept;
};

/**
 * Triggers a crash; for a graphical application this should
 * immediately collapse the stack, show up an error message box
 * containing the error message and then call std::terminate
 * @throw [QF_Exception](QF_Exception.md)
 * @param format Format string in sprintf style
 * @see cppreference for [fprintf](https://en.cppreference.com/w/c/io/fprintf)
 */
#define QF_throw(format, ...) throw QF_Exception::create((format), ##__VA_ARGS__)

#ifdef NDEBUG
#define QF_throw_debug(format, ...) static_cast<void>((format), ##__VA_ARGS__)
#endif /* NDEBUG */

#ifndef QF_throw_debug
/**
 * Triggers a crash; only works when NDEBUG is not defined
 * @throw [QF_Exception](QF_Exception.md)
 * @param format Format string in sprintf style
 * @see cppreference for [fprintf](https://en.cppreference.com/w/c/io/fprintf)
 * @note This only works for non-RELEASE builds
 */
#define QF_throw_debug(format, ...) QF_throw((format), ##__VA_ARGS__)
#endif /* QF_throw_debug */

#endif /* CORE_EXCEPTION_HH */
