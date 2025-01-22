#ifndef CORE_CONFIG_HH
#define CORE_CONFIG_HH 1
#pragma once

/**
 * Config variable flags used in calls for
 * registering things with config::add
 */
enum QF_ConfigFlags : unsigned int {
    FCONFIG_NOTHING = 0x0000, ///< Default empty bit field
    FCONFIG_NO_LOAD = 0x0001, ///< Variable is ignored during loading
    FCONFIG_NO_SAVE = 0x0002, ///< Variable is ignored during saving
};

namespace config
{
/**
 * Parses a config file and appends its contents
 * into the existing configuration registry; mind you
 * this may be called multiple times and will override
 * values from the previously parsed files
 * @param filename Virtual file path
 */
void load(const char *filename);

/**
 * Saves the current configuration registry into a file
 * @param filename Virtual file path
 */
void save(const char *filename);
} // namespace config

namespace config
{
void add(const char *name, int &vref, QF_ConfigFlags flags = FCONFIG_NOTHING);
void add(const char *name, bool &vref, QF_ConfigFlags flags = FCONFIG_NOTHING);
void add(const char *name, float &vref, QF_ConfigFlags flags = FCONFIG_NOTHING);
void add(const char *name, std::size_t &vref, QF_ConfigFlags flags = FCONFIG_NOTHING);
void add(const char *name, unsigned int &vref, QF_ConfigFlags flags = FCONFIG_NOTHING);
void add(const char *name, char *vref, std::size_t size, QF_ConfigFlags flags = FCONFIG_NOTHING);
} // namespace config

namespace config
{
/**
 * Converts a value into a string
 * @param name Config value name
 * @returns Config value as a string or nullptr if not found
 */
const char *get_string(const char *name);
} // namespace config

namespace config
{
/**
 * Sets a config value from a string
 * @param name Config value name
 * @param string Config value as a string
 */
void set_string(const char *name, const char *string);
} // namespace config

#endif /* CORE_CONFIG_HH */
