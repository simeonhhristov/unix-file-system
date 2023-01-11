#pragma once
#include <string>

namespace Errors {
    const std::string NO_SUCH_FILE_OR_DIR = "ERROR: No such file or directory";
    const std::string FILE_NOT_DIRECTORY = ": File is not a directory.";
    const std::string FILE_DOES_NOT_EXIST = ": File does not exist.";
    const std::string FILE_ALREADY_EXISTS = ": File already exists.";
    const std::string FILE_NOT_ORDINARY = ": File is not an ordinary file";
    const std::string FILE_IS_DIRECTORY = ": File is a directory.";

    const std::string DIRECTORY_ALREADY_EXISTS = ": Directory already exists";
    const std::string DIRECTORY_DOES_NOT_EXIST = ": Directory does not exist.";
    const std::string FILE_IS_NOT_DIRECTORY = ": File is not a directory";
    const std::string CANT_DELETE_CURRENT_DIR = "ERROR: Can't delete current directory";
    const std::string DIR_IS_NOT_EMPTY = ": Directory is not empty";

    const std::string NOT_SPECIFIED_FILE = "ERROR: No file name specified.";
    const std::string NOT_SPECIFIED_DESTINATION = "ERROR: No destination directory name specified.";
    const std::string INVALID_PATH = ": Invalid path specified.";

    const std::string INVALID_COMMAND = ": Is not a valid command";
    const std::string MANY_OUTPUT_REDIRECTION_OPERATORS = "ERROR: There can be only 1 output redirection operator";
    const std::string MANY_ARGS_POST_OUTPUT_REDIRECTION_OPERATOR = "ERROR: Only one argument is allowed after the output redirection operator";
    const std::string COMMAND_WITHOUT_OUTPUT_REDIRECTION = ": Command does not require an output redirection operator";
    const std::string INVALID_NUMBER_OF_ARGUMENTS = ": Invalid number of arguments";
    const std::string ARGUMENT_WITH_INVALID_SYMBOLS = ": Argument contains invalid symbols (`, \\, |, >)";
}