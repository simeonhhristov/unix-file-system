#include <iostream>
#include <string>
#include <vector>
#include "../../file-system-utils/string_utils.hpp"
#include "input_handler.hpp"

InputHandler::InputHandler()
{
    stringUtils = StringUtils();
}

void InputHandler::validateArguments(const std::vector<std::string> &arguments)
{
    for (size_t i = 0; i < arguments.size(); i++)
    {
        if (arguments[i] == ">")
        {
            continue;
        }
        if (!isValidArgument(arguments[i]))
        {
            // empty vector signals invalid input to the engine
            std::string error = arguments[i] + " contains invalid symbols (`, \\, |, >)";
            throw std::invalid_argument(error);
        }
    }
}

bool InputHandler::isValidArgument(const std::string &input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] == INVALID_CHARACTERS[0] ||
            input[i] == INVALID_CHARACTERS[1] ||
            input[i] == INVALID_CHARACTERS[2] ||
            input[i] == INVALID_CHARACTERS[3])
        {
            return false;
        }
    }

    return true;
}
void InputHandler::validateCommand(const std::vector<std::string> &arguments)
{
    for (int i = 0; i < NUM_OF_VALID_COMMANDS; i++)
    {
        if (arguments[0] == VALID_COMMANDS[i])
        {
            return;
        }
    }
    std::string error = arguments[0] + " is not a valid command";
    throw std::invalid_argument(error);
}

// validate position and number of occurances of '>'
void InputHandler::validateOutputRedirectOccurrenceAndPosition(const std::vector<std::string> &arguments)
{
    int occurences = 0;
    for (int i = 1; i < arguments.size(); i++)
    {
        if (arguments[i] == ">")
        {
            occurences++;

            if (occurences > 1)
            {
                throw std::invalid_argument("A maximum of 1 output redirection operator is allowed");
            }
            if (arguments.size() - i > 2)
            {
                throw std::invalid_argument("Only one argument is allowed after the output redirection operator");
            }
        }
    }

    if (occurences == 1 && arguments[0] != "cat")
    {
        std::string error = arguments[0] + " does not require an output redirection operator";
        throw std::invalid_argument(error);
    }
}

std::vector<std::string> InputHandler::readInput()
{
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> arguments;

    input = stringUtils.removeWhiteSpaces(input);
    if (input.size() == 0)
    {
        return arguments;
    }

    arguments = stringUtils.segmentString(input, ' ');
    validateCommand(arguments);                             // check for valid command
    validateArguments(arguments);                           // check for invalid symbols
    validateOutputRedirectOccurrenceAndPosition(arguments); // check position and number of occurances for '>'

    return arguments;
}

std::string InputHandler::readInputForNewFile()
{
    std::string currentLine;
    std::string result;

    while (currentLine != "." && !std::cin.eof())
    {
        std::getline(std::cin, currentLine);
        result += '\n' + currentLine;
    }

    // remove the interupt input character '.'
    result.pop_back();
    return result;
}