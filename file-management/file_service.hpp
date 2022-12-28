#pragma once
#include "../model/file-types/directory.hpp"
#include "../model/file-types/ordinary_file.hpp"
#include "../model/file-types/symbolic_link.hpp"
#include "file_repository.hpp"

class FileService
{
private:
    FileRepository *repository;
    Directory *currentDirectory;

public:
    FileService();
    FileService(FileRepository *repository, Directory *currentDirectory);
    FileService(const FileService &other) = delete;
    FileService& operator=(const FileService &other) = delete;
    ~FileService();

    void changeDirectory(const std::string &path); // cd 
    void printWorkingDirectory(); // pwd
    void listItems(); // ls
    void concatenate(); // cat
    void copyFiles(); // cp
    void removeFiles(); // rm
    void makeDirectory(); // mkdir
    void removeDirectory(); // rmdir
    void makeSymbolicLink(); // ln
    void printStat(); // stat
};