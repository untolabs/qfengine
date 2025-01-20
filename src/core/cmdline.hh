#ifndef CORE_CMDLINE_HH
#define CORE_CMDLINE_HH 1
#pragma once

namespace cmdline
{
/**
 * Initializes the command line options
 * registry with the classic argv values
 * @param argc Argument count
 * @param argv Argument strings
 */
void init(int argc, char **argv);

/**
 * Inserts an option into the registry
 * @param option Command line option
 * @param argument Optional argument value
 */
void insert(const char *option, const char *argument = nullptr);

/**
 * Returns an option's argument
 * @param option Command line option
 * @returns Option's argument or NULL if there is none
 */
const char *get(const char *option);

/**
 * Checks if the registry has an option
 * @param option Command line option
 * @returns true when the option is present
 */
bool contains(const char *option);
} // namespace cmdline

#endif /* CORE_CMDLINE_HH */
