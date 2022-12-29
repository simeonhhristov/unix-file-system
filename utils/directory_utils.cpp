#include "directory_utils.hpp"

std::string &DirectoryUtils::getFullPath(Directory *directory)
{
    std::string *result = new std::string("");
    if (!directory)
    {
        return *result;
    }

    Directory *current = directory;
    while (current)
    {
        *result = current->getName() + "/" + *result;
        current = current->getParent();
    }

    if (result->size() > 1)
    {
        result->pop_back();
        return *result;
    }
    return *result;
}