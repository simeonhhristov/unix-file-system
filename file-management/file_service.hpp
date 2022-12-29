#pragma once
#include <vector>
#include "../model/file-types/directory.hpp"
#include "../model/file-types/ordinary_file.hpp"
#include "../model/file-types/symbolic_link.hpp"
#include "../utils/directory_utils.hpp"
#include "file_repository.hpp"

class FileService
{
private:
    FileRepository *repository;
    Directory *currentDirectory;
    DirectoryUtils *directoryUtils;

public:
    FileService(FileRepository *repository, Directory *root);
    FileService() = delete;
    FileService(const FileService &other) = delete;
    FileService &operator=(const FileService &other) = delete;
    ~FileService();

    std::string getWorkingDirectory();                   // pwd
    Directory *changeDirectory(const std::string &path); // cd
    std::vector<Directory *> listItems();                // ls
    void concatenate();                                  // cat
    void copyFiles();                                    // cp
    void removeFiles();                                  // rm
    void makeDirectory();                                // mkdir
    void removeDirectory();                              // rmdir
    void makeSymbolicLink();                             // ln
    std::string getStat();                               // stat
};