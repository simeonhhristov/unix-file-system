#pragma once
#include <string>

namespace cli {
    const std::string VALID_COMMANDS[] = {"pwd", "cd", "ls", "cat", "cp", "rm", "mkdir", "rmdir", "ln", "stat"};
    const int NUM_OF_VALID_COMMANDS = 10;
    
    const char INVALID_CHARACTERS[] = {'\\', '|', '`', '>'};
}