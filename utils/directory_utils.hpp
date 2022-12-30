#pragma once
#include <string>
#include <vector>
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
public:
    std::string &getFullPath(Directory *directory) const;
    Directory *findDirectory(Directory *startingDirectory, const std::string &path) const;
    File *findFile(Directory * startingDirectory, const std::string &path) const;
};