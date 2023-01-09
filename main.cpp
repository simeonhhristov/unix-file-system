#include <iostream>
#include <vector>
#include <string>
// #include "file-system-cli/input-handling/input-handler.hpp"

enum class Commands
    {
        pwd,
        cd,
        ls,
        cat,
        cp,
        rm,
        mkdir,
        rmdir,
        ln,
        stat
    };

int main()
{
    // InputHandler handler = InputHandler();
// {"pwd", "ls", "cd", "cat", "cp", "rm", "rmdir", "mkdir", "ln", "stat"}
    std::vector<std::string> output;
    output.push_back("pwd");
    output.push_back("cd");
    output.push_back("ls");
    output.push_back("cat");
    output.push_back("cp");
    output.push_back("rm");
    output.push_back("rmdir");
    output.push_back("mkdir");
    output.push_back("ln");
    output.push_back("stat");

    int i = -4;
    switch (Commands(i))
    {
    case Commands::pwd:
        std::cout << "pwd";
    case Commands::cp:
        std::cout << "cp";
    }
    
}