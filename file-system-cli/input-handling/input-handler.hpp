#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../../file-system-utils/string_utils.hpp"

static const char INVALID_CHARACTERS[] = {'\\', '|', '`', '>'};
static const std::string VALID_COMMANDS[] = {"pwd", "cd", "ls", "cat", "cp", "rm", "mkdir", "rmdir", "ln", "stat"};
static const int NUM_OF_VALID_COMMANDS = 10;

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