#pragma once
#include <vector>
#include <string>
#include "../../file-system-domain/file-management/file_service.hpp"
#include "../input-handling/input-handler.hpp"

class Engine
{
private:
    FileService *fileService;
    InputHandler inputHandler;

public:
    Engine();
    Engine(const Engine &other) = delete;
    Engine &operator=(const Engine &other) = delete;
    ~Engine();

    void run();

private:
    void resolveInput(std::vector<std::string> &inputArguments);
    int getCommandId(const std::string &command);

    void printWorkingDirectory();                                    // pwd
    void changeDirectory(std::vector<std::string> &inputArguments);  // cd
    void listFiles(std::vector<std::string> &inputArguments);        // ls
    void concatenateFiles(std::vector<std::string> &inputArguments); // cat
    void copyFiles(std::vector<std::string> &inputArguments);        // cp
    void removeFiles(std::vector<std::string> &inputArguments);      // rm
    void makeDirectory(std::vector<std::string> &inputArguments);    // mkdir
    void removeDirectory(std::vector<std::string> &inputArguments);  // rmdir
    void makeSymbolicLink(std::vector<std::string> &inputArguments); // ln
    void printStat(std::vector<std::string> &inputArguments);        // stat

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
};