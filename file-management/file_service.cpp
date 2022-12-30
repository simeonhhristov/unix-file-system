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
    Directory * result = directoryUtils.find(currentDirectory, path);
    if (result)
    {
        currentDirectory = result;
    }
    
    return result;
}

std::vector<std::string> FileService::listItems(const std::string &path) const
{}

void FileService::concatenate() 
{}
void FileService::copyFiles() 
{}
void FileService::removeFiles() 
{}
void FileService::makeDirectory() 
{}
void FileService::removeDirectory() 
{}
void FileService::makeSymbolicLink() 
{}
std::string FileService::getStat() 
{}