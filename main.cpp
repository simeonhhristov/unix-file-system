#include <iostream>
#include <vector>
#include <string>
#include "file-system-cli/input-handling/input-handler.hpp"

int main()
{
    InputHandler handler = InputHandler();

    std::vector<std::string> output = handler.readInput();

    for (size_t i = 0; i < output.size(); i++)
    {
        std::cout << output[i] << "\n";
    }
    
}