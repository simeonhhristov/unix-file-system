#include <vector>
#include <string>
#include "file_service.hpp"

FileService::FileService(FileRepository *repository, Directory *root)
{
    this->repository = repository;
    this->currentDirectory = root;
    directoryUtils = DirectoryUtils();
}

FileService::~FileService()
{
    delete repository;
    delete currentDirectory;
}

std::string FileService::getWorkingDirectory() const
{
    return directoryUtils.getFullPath(currentDirectory);
}

Directory *FileService::changeDirectory(const std::string &path)
{
    Directory *result = directoryUtils.findDirectory(currentDirectory, path);
    if (result)
    {
        currentDirectory = result;
    }

    return result;
}

std::vector<std::string> FileService::getContentsList(const std::string &path) const
{
    Directory *target = directoryUtils.findDirectory(currentDirectory, path);
    std::vector<std::string> result;

    if (!target)
    {
        throw std::invalid_argument("No such directory");
    }

    std::vector<File *> subFiles = target->getSubFiles();
    for (int i = 0; i < subFiles.size(); i++)
    {
        result.push_back(subFiles[i]->getName());
    }

    return result;
}

void FileService::concatenate(const std::vector<std::string> &filePaths, const std::string &destinationFile)
{
}

void FileService::concatenate(const std::string &content, const std::string &destinationFile)
{
}

void FileService::copyFiles()
{
}
void FileService::removeFiles()
{
}
void FileService::makeDirectory()
{
}
void FileService::removeDirectory()
{
}
void FileService::makeSymbolicLink()
{
}

std::string FileService::getStat(const std::string &path) const
{
    File* target = repository->find(currentDirectory, path);
    if (!target)
    {
        throw std::invalid_argument("No such file or directory");
    }
    
    MetaData data = target->getMetaData();
    std::string result;
    
    result += std::to_string(data.fileSize) + " ";
    // result += printFileType(data.fileType) + " ";
    result += std::to_string(data.lastAccessDate) + " ";
    result += std::to_string(data.lastMetaDataModificationDate) + " ";
    result += std::to_string(data.serialNumber);
    
    return result;
}