#ifndef CORE_STRTOOLS_HH
#define CORE_STRTOOLS_HH 1
#pragma once

namespace strtools
{
bool is_whitespace(const std::string &string);
} // namespace strtools

namespace strtools
{
std::vector<std::string> split(const std::string &string, const std::string &separator);
} // namespace strtools

namespace strtools
{
std::string trim_whitespace(const std::string &string);
} // namespace strtools

#endif /* CORE_STRTOOLS_HH */
