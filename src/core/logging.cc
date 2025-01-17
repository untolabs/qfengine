#include "core/precompiled.hh"
#include "core/logging.hh"

static QF_LogFunction log_callback = nullptr;
static QF_LogLevel log_level = DEFAULT_LOG_LEVEL;
static std::mutex log_mutex;

void logging::default_callback(QF_LogLevel level, const char *string, std::size_t size)
{
#ifdef _WIN32
    OutputDebugStringA(string);
#endif

    if(std::cerr.good()) {
        std::cerr << string;
        std::cerr << std::endl;
    }
}

void logging::set_callback(QF_LogFunction callback)
{
    log_mutex.lock();
    log_callback = callback;
    log_mutex.unlock();
}

void logging::set_level(QF_LogLevel level)
{
    log_mutex.lock();
    log_level = level;
    log_mutex.unlock();
}

void logging::printf(QF_LogLevel level, const char *format, ...)
{
    if(level >= log_level) {
        std::va_list va;
        va_start(va, format);
        logging::vprintf(level, format, va);
        va_end(va);
    }
}

void logging::vprintf(QF_LogLevel level, const char *format, std::va_list va)
{
    if(level >= log_level) {
        auto count = stbsp_vsnprintf(nullptr, 0, format, va);
        auto string = std::string(std::size_t(count + 2), char(0x00));
        stbsp_vsnprintf(string.data(), string.size(), format, va);

        if(log_callback == nullptr) {
            log_mutex.lock();
            logging::default_callback(level, string.c_str(), string.size());
            log_mutex.unlock();
        }
        else {
            log_mutex.lock();
            log_callback(level, string.c_str(), string.size());
            log_mutex.unlock();
        }
    }
}
