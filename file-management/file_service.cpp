#include <vector>
#include <string>
#include "file_service.hpp"

FileService::FileService(FileRepository *repository, Directory *root) 
{  
    this->repository = repository;
    this->currentDirectory = root;
    directoryUtils = new DirectoryUtils();
}

FileService::~FileService() 
{  
    delete repository;
    delete currentDirectory;
    delete directoryUtils;
}

std::string FileService::getWorkingDirectory() 
{
    directoryUtils->getFullPath(currentDirectory);
}

Directory *FileService::changeDirectory(const std::string &path) 
{}

std::vector<Directory *> FileService::listItems() 
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