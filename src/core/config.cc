#include "core/precompiled.hh"
#include "core/config.hh"

#include "core/assert.hh"
#include "core/logging.hh"
#include "core/strtools.hh"

constexpr static unsigned int CONFIG_INT    = 0;
constexpr static unsigned int CONFIG_BOOL   = 1;
constexpr static unsigned int CONFIG_FLOAT  = 2;
constexpr static unsigned int CONFIG_SIZE_T = 3;
constexpr static unsigned int CONFIG_UINT   = 4;
constexpr static unsigned int CONFIG_STRING = 5;

struct ConfigValue final {
    QF_ConfigFlags flags;
    unsigned int type;
    std::size_t size;
    void *data_ptr;
};

static std::unordered_map<std::string, ConfigValue> vmap;

static const char *static_asprintf(const char *format, ...)
{
    static std::vector<char> buffer;

    va_list va;
    va_start(va, format);
    buffer.resize(2 + stbsp_vsnprintf(nullptr, 0, format, va));
    stbsp_vsnprintf(buffer.data(), buffer.size(), format, va);
    va_end(va);

    return buffer.data();
}

static const char *value_to_string(const ConfigValue &value)
{
    if(value.type == CONFIG_INT) {
        auto actual_value = reinterpret_cast<const int *>(value.data_ptr)[0];
        return static_asprintf("%d", actual_value);
    }

    if(value.type == CONFIG_BOOL) {
        auto actual_value = reinterpret_cast<const bool *>(value.data_ptr)[0];
        return actual_value ? "true" : "false";
    }

    if(value.type == CONFIG_FLOAT) {
        auto actual_value = reinterpret_cast<const float *>(value.data_ptr)[0];
        return static_asprintf("%f", actual_value);
    }

    if(value.type == CONFIG_SIZE_T) {
        auto actual_value = reinterpret_cast<const std::size_t *>(value.data_ptr)[0];
        return static_asprintf("%zu", actual_value);
    }

    if(value.type == CONFIG_UINT) {
        auto actual_value = reinterpret_cast<const unsigned int *>(value.data_ptr)[0];
        return static_asprintf("%u", actual_value);
    }

    if(value.type == CONFIG_STRING) {
        auto actual_value = reinterpret_cast<const char *>(value.data_ptr);
        return static_asprintf("%.*s", value.size, actual_value);
    }

    return nullptr;
}

static void value_from_string(ConfigValue &value, const char *string)
{
    if(value.type == CONFIG_INT) {
        std::sscanf(string, "%d", reinterpret_cast<int *>(value.data_ptr));
        return;
    }

    if(value.type == CONFIG_BOOL) {
        reinterpret_cast<bool *>(value.data_ptr)[0] = std::strcmp(string, "false") || !std::strcmp(string, "true");
        return;
    }

    if(value.type == CONFIG_FLOAT) {
        std::sscanf(string, "%f", reinterpret_cast<float *>(value.data_ptr));
        return;
    }

    if(value.type == CONFIG_SIZE_T) {
        std::sscanf(string, "%zu", reinterpret_cast<std::size_t *>(value.data_ptr));
        return;
    }

    if(value.type == CONFIG_UINT) {
        std::sscanf(string, "%u", reinterpret_cast<unsigned int *>(value.data_ptr));
        return;
    }

    if(value.type == CONFIG_STRING) {
        std::strncpy(reinterpret_cast<char *>(value.data_ptr), string, value.size);
        return;
    }
}

void config::load(const char *filename)
{
    std::stringstream stream;

    if(auto file = PHYSFS_openRead(filename)) {
        auto count = PHYSFS_fileLength(file);
        auto source = std::string(std::size_t(count + 1), char(0x00));
        PHYSFS_readBytes(file, source.data(), source.size());
        PHYSFS_close(file);
        stream.str(source);
    }

    std::string line;
    while(std::getline(stream, line)) {
        auto c_split = strtools::split(line, "#");
        auto c_pair = strtools::trim_whitespace(c_split[0]);

        if(strtools::is_whitespace(c_pair)) {
            // The meaningful part of the line
            // is empty, assume it's just a separation
            continue;
        }

        // Because the value string may contain
        // stray equal signs, so strtools::split won't work here
        auto kv_separator = c_pair.find_first_of('=');

        if(kv_separator == std::string::npos) {
            // Consider any key-value pair without a valid
            // separator between the key and the value as invalid
            QF_notice("config: %s: invalid key-value pair: '%s' %zu %02X", filename, c_pair.c_str(), c_pair.size());
            continue;
        }

        auto kv_key = strtools::trim_whitespace(c_pair.substr(0, kv_separator));
        auto kv_value = strtools::trim_whitespace(c_pair.substr(kv_separator + 1));

        const auto it = vmap.find(kv_key);

        if(it != vmap.cend()) {
            if(it->second.flags & FCONFIG_NO_LOAD)
                continue;
            value_from_string(it->second, kv_value.c_str());
        }
    }
}

void config::save(const char *filename)
{
    std::stringstream stream;

    for(const auto &it : vmap) {
        if(it.second.flags & FCONFIG_NO_SAVE)
            continue;
        std::string value = value_to_string(it.second);
        stream << static_asprintf("%s = %s", it.first.c_str(), value.c_str());
        stream << std::endl;
    }

    if(auto file = PHYSFS_openWrite(filename)) {
        std::string source = stream.str();
        PHYSFS_writeBytes(file, source.data(), source.size());
        PHYSFS_close(file);
    }
}

void config::add(const char *name, int &vref, QF_ConfigFlags flags)
{
    vmap[name] = ConfigValue{flags, CONFIG_INT, sizeof(int), &vref};
}

void config::add(const char *name, bool &vref, QF_ConfigFlags flags)
{
    vmap[name] = ConfigValue{flags, CONFIG_BOOL, sizeof(bool), &vref};
}

void config::add(const char *name, float &vref, QF_ConfigFlags flags)
{
    vmap[name] = ConfigValue{flags, CONFIG_FLOAT, sizeof(float), &vref};
}

void config::add(const char *name, std::size_t &vref, QF_ConfigFlags flags)
{
    vmap[name] = ConfigValue{flags, CONFIG_SIZE_T, sizeof(std::size_t), &vref};
}

void config::add(const char *name, unsigned int &vref, QF_ConfigFlags flags)
{
    vmap[name] = ConfigValue{flags, CONFIG_UINT, sizeof(unsigned int), &vref};
}

void config::add(const char *name, char *vref, std::size_t size, QF_ConfigFlags flags)
{
    QF_assert_msg(vref && size, "invalid string reference");
    vmap[name] = ConfigValue{flags, CONFIG_STRING, size, vref};
}

const char *config::get_string(const char *name)
{
    const auto it = vmap.find(name);

    if(it == vmap.cend()) {
        QF_verbose("config::get_string: %s: key not found", name);
        return nullptr;
    }

    return value_to_string(it->second);
}

void config::set_string(const char *name, const char *string)
{
    const auto it = vmap.find(name);

    if(it == vmap.cend()) {
        QF_warning("config::set_string: %s: key not found", name);
        return;
    }

    value_from_string(it->second, string);
}
