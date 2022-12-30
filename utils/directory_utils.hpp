#pragma once
#include <string>
#include <vector>
#include "../model/base/file.hpp"
#include "../model/file-types/directory.hpp"

class DirectoryUtils
{
private:
    Directory *goUpTheHierarchy(Directory *directory) const;
    Directory *goDownTheHierarchy(Directory *directory, const std::string &nextDirectoryName) const;
    Directory *goToRoot(Directory * directory) const;
public:
    std::string &getFullPath(Directory *directory) const;
    Directory *find(Directory* startingDirectory, const std::string &path) const;
};