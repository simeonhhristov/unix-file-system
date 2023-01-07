#include "string_utils.hpp"

std::string StringUtils::removeWhiteSpaces(const std::string &input)
{
    std::string result = "";

    for (int i = 0; i < input.length();)
    {
        if (input[i] == ' ')
        {
            if (i == 0 || i == input.length() - 1)
            {
                i++;
                continue;
            }
            while (input[i + 1] == ' ')
            {
                i++;
            }
        }
        result += input[i++];
    }
    return result;
}

std::vector<std::string> StringUtils::segmentString(const std::string &input, char delimiter)
{
    std::string trimmed = removeWhiteSpaces(input);
    if (trimmed.back() != delimiter)
    {
        trimmed.push_back(delimiter);
    }
    std::vector<std::string> tokens;

    int pos = 0;
    std::string token;
    while ((pos = trimmed.find(delimiter)) != std::string::npos)
    {
        token = trimmed.substr(0, pos);
        tokens.push_back(token);
        trimmed.erase(0, pos + 1);
    }

    return tokens;
}