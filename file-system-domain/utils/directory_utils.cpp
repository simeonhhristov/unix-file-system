#include <string>
#include <vector>
#include "directory_utils.hpp"
#include "string_utils.hpp"

Directory *DirectoryUtils::traverseDirectories(Directory *startingDirectory, std::vector<std::string> &pathSegments) const
{
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

        if (pathSegments[i] == ".")
        {
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

Directory *DirectoryUtils::traverseAndCreateDirectories(Directory *startingDirectory, std::vector<std::string> &pathSegments) const
{
    Directory *currentDirectory = startingDirectory;
    int startIdx = 0;

    // check for absolute path
    if (!pathSegments.empty() &&
        pathSegments[0] == "")
    {
        currentDirectory = goToRoot(currentDirectory);
        startIdx = 1;
    }

    FileFactory factory = FileFactory();
    for (int i = startIdx; i < pathSegments.size(); i++)
    {
        if (pathSegments[i] == "..")
        {
            currentDirectory = goUpTheHierarchy(currentDirectory);
            continue;
        }
        if (pathSegments[i] == ".")
        {
            continue;
        }

        Directory *nextDirectory = goDownTheHierarchy(currentDirectory, pathSegments[i]);

        // if current is null create it
        if (!nextDirectory)
        {
            nextDirectory = factory.createDirectory(pathSegments[i], currentDirectory);
        }
        currentDirectory = nextDirectory;
    }
    return currentDirectory;
}

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

Directory *DirectoryUtils::findDirectory(Directory *startingDirectory, const std::string &path) const
{
    StringUtils stringUtils = StringUtils();
    std::vector<std::string> pathSegments = stringUtils.segmentString(path, '/');

    return traverseDirectories(startingDirectory, pathSegments);
}

File *DirectoryUtils::findFile(Directory *startingDirectory, const std::string &path) const
{
    StringUtils stringUtils = StringUtils();
    std::vector<std::string> pathSegments = stringUtils.segmentString(path, '/');
    std::string fileName;

    // extract file name from path segments
    fileName = pathSegments[pathSegments.size() - 1];
    pathSegments.pop_back();

    Directory *fileLocation = traverseDirectories(startingDirectory, pathSegments);
    if (!fileLocation)
    {
        return nullptr;
    }

    // search for file in directory
    std::vector<File *> subFiles = fileLocation->getSubFiles();
    for (size_t i = 0; i < subFiles.size(); i++)
    {
        if (subFiles[i]->getName() == fileName)
        {
            // return file pointer in coresponding type
            switch (subFiles[i]->getMetaData().fileType)
            {
            case FileType::File:
            {
                OrdinaryFile *result = dynamic_cast<OrdinaryFile *>(subFiles[i]);
                return result;
            }
            case FileType::Symlink:
            {
                SymbolicLink *result = dynamic_cast<SymbolicLink *>(subFiles[i]);
                return result;
            }
            case FileType::Directory:
            {
                Directory *result = dynamic_cast<Directory *>(subFiles[i]);
                return result;
            }
            }
        }
    }
    return nullptr;
}

void DirectoryUtils::createDirectory(Directory *startingDirectory, const std::string &path) const
{
    StringUtils stringUtils = StringUtils();
    std::vector<std::string> pathSegments = stringUtils.segmentString(path, '/');
    Directory *target = traverseDirectories(startingDirectory, pathSegments);
    if (target)
    {
        throw std::invalid_argument("Directory already exists");
    }
    traverseAndCreateDirectories(startingDirectory, pathSegments);
}

void DirectoryUtils::createFile(Directory *startingDirectory, const std::string &path, const std::string &data, FileType fileType) const
{
    StringUtils stringUtils = StringUtils();
    std::vector<std::string> pathSegments = stringUtils.segmentString(path, '/');
    std::string fileName;

    // extract file name from path segments
    fileName = pathSegments[pathSegments.size() - 1];
    pathSegments.pop_back();

    Directory *fileLocation = traverseAndCreateDirectories(startingDirectory, pathSegments);
    File *target = findFile(fileLocation, fileName);
    if (target)
    {
        throw std::invalid_argument("File already exists");
    }
     
    FileFactory factory = FileFactory();
    switch (fileType)
    {
    case FileType::File:
    {
        factory.createOrdinaryFile(fileName, data, fileLocation);
        break;
    }
    case FileType::Symlink:
    {
        factory.createSymbolicLink(fileName, data, fileLocation);
        break;
    }
    case FileType::Directory:
        break;
    }
}