#include "core/precompiled.hh"
#include "core/exception.hh"

const char *QF_Exception::what(void) const noexcept
{
    return buffer;
}

QF_Exception QF_Exception::create(const char *format, ...) noexcept
{
    std::va_list va;
    QF_Exception result;

    va_start(va, format);
    stbsp_vsnprintf(result.buffer, sizeof(result.buffer), format, va);
    va_end(va);

    return result;
}
