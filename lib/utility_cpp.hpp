//Utility functions for the C++ standard
#include <cstddef>
#include <string>

size_t length (const std::string input)
{
    return input.size();
}

std::string substring(const std::string source,const size_t start, const size_t end)
{
    return source.substr(start, end);
}