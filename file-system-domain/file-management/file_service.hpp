#pragma once
#include <vector>
#include <string>
#include "file_repository.hpp"
#include "../utils/directory_utils.hpp"
#include "../../file-system-utils/string_utils.hpp"
#include "../model/file-types/directory.hpp"

class FileService
{
private:
    FileRepository *repository;
    Directory *currentDirectory;
    DirectoryUtils directoryUtils;
    StringUtils stringUtils;

public:
    FileService();
    FileService(const FileService &other) = delete;
    FileService &operator=(const FileService &other) = delete;
    ~FileService();

    std::string getWorkingDirectory() const;                                                         // pwd
    std::string changeDirectory(const std::string &path);                                            // cd
    std::string getContentsList(const std::string &path) const;                                      // ls
    void concatenate(const std::vector<std::string> &filePaths, const std::string &destinationFile); // cat
    void createOrdinaryFile(const std::string &content, const std::string &destinationFile);         // cat (touch)
    std::string getConcatenatedContents(const std::vector<std::string> &filePaths);                  // cat
    void copyFiles(const std::vector<std::string> &filePaths, const std::string &destinationPath);   // cp
    void removeFile(const std::string &filePath);                                                    // rm
    void makeDirectory(const std::string &filePath);                                                 // mkdir
    void removeDirectory(const std::string &filePath);                                               // rmdir
    void makeSymbolicLink(const std::string &targetPath, const std::string &linkLocation);           // ln
    std::string getStat(const std::string &path) const;                                              // stat
};