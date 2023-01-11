#pragma once
#include <string>
#include <vector>
#include "../file-management/file_factory.hpp"
#include "../model/base/file.hpp"
#include "../model/file-types/directory.hpp"
#include "../model/file-types/ordinary_file.hpp"
#include "../model/file-types/symbolic_link.hpp"

class DirectoryUtils
{
private:
    Directory *goUpTheHierarchy(Directory *directory) const;
    Directory *goDownTheHierarchy(Directory *directory, const std::string &nextDirectoryName) const;
    Directory *goToRoot(Directory *directory) const;
    Directory *traverseDirectories(Directory *startingDirectory, std::vector<std::string> &pathSegments) const;
    Directory *traverseAndCreateDirectories(Directory *startingDirectory, std::vector<std::string> &pathSegments) const;
public:
    std::string &getFullPath(Directory *directory) const;
    Directory *findDirectory(Directory *startingDirectory, const std::string &path) const;
    File *findFile(Directory * startingDirectory, const std::string &path) const;
    void createDirectory(Directory * startingDirectory, const std::string &path) const;
    void createFile(Directory *startingDirectory, const std::string &path, const std::string &data, FileType type) const;
    OrdinaryFile *getFileFromSymLink(Directory *startingDirectory, const std::string &path);
    std::string createFileCopyName(Directory *targetDirectory, const std::string fileName);
};