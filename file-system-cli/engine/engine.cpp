#include <iostream>
#include <string>
#include <vector>
#include "engine.hpp"

Engine::Engine()
{
    fileService = new FileService();
    inputHandler = InputHandler();
}

Engine::~Engine()
{
    delete fileService;
}

void Engine::run()
{
    while (true)
    {
        std::vector<std::string> inputArguments;
        try
        {
            inputArguments = inputHandler.readInput();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        resolveInput(inputArguments);
    }
}
int Engine::getCommandId(const std::string &command)
{
    for (int i = 0; i < NUM_OF_VALID_COMMANDS; i++)
    {
        if (command == VALID_COMMANDS[i])
        {
            return i;
        }
    }
    return -1;
}

void Engine::resolveInput(std::vector<std::string> &inputArguments)
{
    int commandId = getCommandId(inputArguments[0]);
    switch (Commands(commandId))
    {
    case Commands::pwd:
    {
        printWorkingDirectory();
        break;
    }
    case Commands::cd:
    {
        changeDirectory(inputArguments);
        break;
    }
    case Commands::ls:
    {
        listFiles(inputArguments);
        break;
    }
    case Commands::cat:
    {
        concatenateFiles(inputArguments);
        break;
    }
    case Commands::cp:
    {
        copyFiles(inputArguments);
        break;
    }
    case Commands::rm:
    {
        removeFiles(inputArguments);
        break;
    }
    case Commands::rmdir:
    {
        removeDirectory(inputArguments);
        break;
    }
    case Commands::mkdir:
    {
        makeDirectory(inputArguments);
        break;
    }
    case Commands::ln:
    {
        makeSymbolicLink(inputArguments);
        break;
    }
    case Commands::stat:
    {
        printStat(inputArguments);
        break;
    }
    default:
        std::cerr << "Invalid command";
    }
}

void Engine::printWorkingDirectory()
{
}
void Engine::changeDirectory(std::vector<std::string> &inputArguments)
{
}
void Engine::listFiles(std::vector<std::string> &inputArguments)
{
}
void Engine::concatenateFiles(std::vector<std::string> &inputArguments)
{
}
void Engine::copyFiles(std::vector<std::string> &inputArguments)
{
}
void Engine::removeFiles(std::vector<std::string> &inputArguments)
{
}
void Engine::makeDirectory(std::vector<std::string> &inputArguments)
{
}
void Engine::removeDirectory(std::vector<std::string> &inputArguments)
{
}
void Engine::makeSymbolicLink(std::vector<std::string> &inputArguments)
{
}
void Engine::printStat(std::vector<std::string> &inputArguments)
{
}