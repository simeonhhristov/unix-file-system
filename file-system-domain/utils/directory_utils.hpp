#pragma once
#include <string>
#include <vector>
#include "../../file-system-utils/string_utils.hpp"
#include "../model/base/file.hpp"
#include "../model/file-types/directory.hpp"
#include "../model/file-types/ordinary_file.hpp"

class DirectoryUtils
{
private:
    StringUtils stringUtils;

    Directory *goUpTheHierarchy(Directory *directory) const;
    Directory *goDownTheHierarchy(Directory *directory, const std::string &nextDirectoryName) const;
    Directory *goToRoot(Directory *directory) const;
    Directory *traverseDirectories(Directory *startingDirectory, std::vector<std::string> &pathSegments) const;
    Directory *traverseAndCreateDirectories(Directory *startingDirectory, std::vector<std::string> &pathSegments) const;
public:
    DirectoryUtils();

    std::string &getFullPath(Directory *directory) const;
    Directory *findDirectory(Directory *startingDirectory, const std::string &path) const;
    File *findFile(Directory * startingDirectory, const std::string &path) const;
    void createDirectory(Directory * startingDirectory, const std::string &path) const;
    void createFile(Directory *startingDirectory, const std::string &path, const std::string &data, FileType type) const;
    OrdinaryFile *getFileFromSymLink(Directory *startingDirectory, const std::string &path);
    std::string createFileCopyName(Directory *targetDirectory, const std::string fileName);
};