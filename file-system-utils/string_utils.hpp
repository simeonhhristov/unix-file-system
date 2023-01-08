#pragma once
#include <string>
#include <vector>

class StringUtils
{
public:
    std::string removeWhiteSpaces(const std::string &input);
    std::vector<std::string> segmentString(const std::string &input, char delimiter);
    std::string getLastAfter(const std::string text,const std::string &delimeter);
};