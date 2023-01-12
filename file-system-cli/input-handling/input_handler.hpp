#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../../file-system-utils/string_utils.hpp"

class InputHandler
{
private:
    StringUtils stringUtils;
    void validateCommand(const std::vector<std::string> &arguments);
    void validateArguments(const std::vector<std::string> &arguments);
    bool isValidArgument(const std::string &argument);
    void validateOutputRedirectOccurrenceAndPosition(const std::vector<std::string> &arguments);

public:
    InputHandler();
    std::vector<std::string> readInput();
    std::string readInputForNewFile();
};