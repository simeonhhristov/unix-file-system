#include <iostream>
#include <vector>
#include <string>
#include "file-system-cli/engine/engine.hpp"

int main()
{
//     // InputHandler handler = InputHandler();
// // {"pwd", "ls", "cd", "cat", "cp", "rm", "rmdir", "mkdir", "ln", "stat"}
//     std::vector<std::string> output;
//     output.push_back("pwd");
//     output.push_back("cd");
//     output.push_back("ls");
//     output.push_back("cat");
//     output.push_back("cp");
//     output.push_back("rm");
//     output.push_back("rmdir");
//     output.push_back("mkdir");
//     output.push_back("ln");
//     output.push_back("stat");
//     std::vector<std::string> newvec(output.begin(), output.end() - 2);
//     for (size_t i = 0; i < newvec.size(); i++)
//     {
//         std::cout << newvec[i] << " ";
//     }
    Engine engine;
    engine.run();
}