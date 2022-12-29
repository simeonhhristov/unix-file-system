#pragma once
#include <string>
#include <vector>
#include "../model/base/file.hpp"
#include "../model/file-types/directory.hpp"

class DirectoryUtils
{
public:
    std::string &getFullPath(Directory *directory);
};