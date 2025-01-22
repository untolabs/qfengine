#include "core/precompiled.hh"
#include "core/strtools.hh"

constexpr static const char *WHITESPACE_CHARS = " \t\r\n";

bool strtools::is_whitespace(const std::string &string)
{
    if(string.find_first_not_of(WHITESPACE_CHARS) == std::string::npos)
        return true;
    if((string.size() == 1) && string[0] == 0x00)
        return true;
    return string.empty();
}

std::vector<std::string> strtools::split(const std::string &string, const std::string &separator)
{
    std::size_t pos = 0;
    std::size_t prev = 0;
    std::vector<std::string> result;

    while((pos = string.find(separator, prev)) != std::string::npos) {
        result.push_back(string.substr(prev, pos - prev));
        prev = pos + separator.length();
    }

    if(prev <= string.length())
        result.push_back(string.substr(prev, string.length() - prev));
    return result;
}

std::string strtools::trim_whitespace(const std::string &string)
{
    auto su = string.find_first_not_of(WHITESPACE_CHARS);
    auto sv = string.find_last_not_of(WHITESPACE_CHARS);

    if(su == std::string::npos)
        return std::string();
    return string.substr(su, sv - su + 1);
}
