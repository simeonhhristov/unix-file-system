#include <iostream>
#include <string>
#include <vector>
#include "engine.hpp"
#include "../../file-system-domain/file-management/file_service.hpp"
#include "../input-handling/input_handler.hpp"

Engine::Engine()
{
    currentDirectoryName = "/";
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
            std::cout << currentDirectoryName << " $ ";
            inputArguments = inputHandler.readInput();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            continue;
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
    if (inputArguments.size() == 0)
    {
        return;
    }

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
        std::cerr << "Invalid command"
                  << "\n";
    }
}

void Engine::printWorkingDirectory()
{
    std::cout << fileService->getWorkingDirectory() << "\n";
}

void Engine::changeDirectory(std::vector<std::string> &inputArguments)
{
    if (inputArguments.size() != 2)
    {
        std::cerr << "Invalid number of arguments\n";
        return;
    }

    std::string newDirectory = currentDirectoryName;
    try
    {
        newDirectory = fileService->changeDirectory(inputArguments[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    if (newDirectory.size() == 0)
    {
        currentDirectoryName = "/";
        return;
    }
    currentDirectoryName = newDirectory;
}

void Engine::listFiles(std::vector<std::string> &inputArguments)
{
    if (inputArguments.size() == 1)
    {
        inputArguments.push_back(".");
    }

    if (inputArguments.size() != 2)
    {
        std::cerr << "Invalid number of arguments\n";
        return;
    }

    std::vector<std::string> result;
    try
    {
        result = fileService->getContentsList(inputArguments[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n";
        result = fileService->getContentsList(".");
    }

    for (size_t i = 0; i < result.size(); i++)
    {
        std::cout << result[i] << " ";
    }
    std::cout << "\n";
}

void Engine::concatenateFiles(std::vector<std::string> &inputArguments)
{
    if (inputArguments.size() == 1)
    {
        std::string input = inputHandler.readInputForNewFile();
        std::cout << input << "\n";
        return;
    }

    // remove 'cat' command argument
    inputArguments.erase(inputArguments.begin());

    try
    {
        // cases with output redirection
        if (inputArguments[inputArguments.size() - 2] == ">")
        {
            // read from console
            if (inputArguments.size() == 2)
            {
                std::string input = inputHandler.readInputForNewFile();
                fileService->createOrdinaryFile(input, inputArguments[inputArguments.size() - 1]);
            }
            // concatenate files
            else
            {
                std::vector<std::string> targetFiles(inputArguments.begin(), inputArguments.end() - 2);
                fileService->concatenate(targetFiles, inputArguments[inputArguments.size() - 1]);
            }
            return;
        }

        std::string output = fileService->getConcatenatedContents(inputArguments);
        std::cout << output << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Engine::copyFiles(std::vector<std::string> &inputArguments)
{
}

void Engine::removeFiles(std::vector<std::string> &inputArguments)
{
    for (int i = 1; i < inputArguments.size(); i++)
    {
        try
        {
            fileService->removeFile(inputArguments[i]);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void Engine::makeDirectory(std::vector<std::string> &inputArguments)
{
    for (int i = 1; i < inputArguments.size(); i++)
    {
        try
        {
            fileService->makeDirectory(inputArguments[i]);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void Engine::removeDirectory(std::vector<std::string> &inputArguments)
{
    for (int i = 1; i < inputArguments.size(); i++)
    {
        try
        {
            fileService->removeDirectory(inputArguments[i]);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void Engine::makeSymbolicLink(std::vector<std::string> &inputArguments)
{
    if (inputArguments.size() != 3)
    {
        std::cerr << "Invalid number of arguments\n";
        return;
    }

    try
    {
        fileService->makeSymbolicLink(inputArguments[1], inputArguments[2]);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Engine::printStat(std::vector<std::string> &inputArguments)
{
    if (inputArguments.size() == 1)
    {
        std::cerr << "Invalid number of arguments\n";
        return;
    }

    for (size_t i = 1; i < inputArguments.size(); i++)
    {
        std::string output;
        try
        {
            output = fileService->getStat(inputArguments[i]);
            std::cout << output << "\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}