#include "directory_utils.hpp"
#include "string_utils.hpp"

Directory *DirectoryUtils::goUpTheHierarchy(Directory *directory) const
{
    // guard for nullptr
    if (!directory)
    {
        return nullptr;
    }

    // if in root do not advance
    if (!directory->getParent())
    {
        return directory;
    }

    return directory->getParent();
}

Directory *DirectoryUtils::goDownTheHierarchy(Directory *directory, const std::string &nextDirectoryName) const
{
    // guard for nullptr
    if (!directory)
    {
        return nullptr;
    }

    std::vector<File *> subFiles = directory->getSubFiles();
    for (int i = 0; i < subFiles.size(); i++)
    {
        if (subFiles[i]->getName() == nextDirectoryName)
        {
            // returns nullptr if object is not directory
            return dynamic_cast<Directory *>(subFiles[i]);
        }
    }

    return nullptr;
}

Directory *DirectoryUtils::goToRoot(Directory *directory) const
{
    Directory *current = directory;
    Directory *prev = goUpTheHierarchy(current);
    while (prev != current)
    {
        current = prev;
        prev = goUpTheHierarchy(current);
    }
    return current;
}

std::string &DirectoryUtils::getFullPath(Directory *directory) const
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

Directory *DirectoryUtils::find(Directory *startingDirectory, const std::string &path) const
{
    StringUtils stringUtils = StringUtils();
    std::vector<std::string> pathSegments = stringUtils.segmentString(path, '/');

    Directory *currentDirectory = startingDirectory;
    int startIdx = 0;

    // check for absolute path
    if (!pathSegments.empty() &&
        pathSegments[0] == "")
    {
        currentDirectory = goToRoot(currentDirectory);
        startIdx = 1;
    }

    for (int i = startIdx; i < pathSegments.size(); i++)
    {
        if (pathSegments[i] == "..")
        {
            currentDirectory = goUpTheHierarchy(currentDirectory);
            continue;
        }
        currentDirectory = goDownTheHierarchy(currentDirectory, pathSegments[i]);

        // if current is null directory does not exist
        if (!currentDirectory)
        {
            break;
        }
    }

    return currentDirectory;
}