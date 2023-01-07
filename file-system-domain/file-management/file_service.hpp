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
    DirectoryUtils directoryUtils;

public:
    FileService(FileRepository *repository, Directory *root);
    FileService() = delete;
    FileService(const FileService &other) = delete;
    FileService &operator=(const FileService &other) = delete;
    ~FileService();

    std::string getWorkingDirectory() const;                                                         // pwd
    Directory *changeDirectory(const std::string &path);                                             // cd
    std::vector<std::string> getContentsList(const std::string &path) const;                         // ls
    void concatenate(const std::vector<std::string> &filePaths, const std::string &destinationFile); // cat
    void createOrdinaryFile(const std::string &content, const std::string &destinationFile);         // touch
    void copyFiles(const std::vector<std::string> &filePaths, const std::string &destinationPath);   // cp
    void removeFile(const std::string &filePath);                                                    // rm
    void makeDirectory(const std::string &filePath);                                                 // mkdir
    void removeDirectory(const std::string &filePath);                                               // rmdir
    void makeSymbolicLink(const std::string &targetPath, const std::string &linkLocation);           // ln
    std::string getStat(const std::string &path) const;                                              // stat
};