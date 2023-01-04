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
    if (repository->find(currentDirectory, destinationFile))
    {
        throw std::invalid_argument("Destination file already exists");
    }
}

void FileService::concatenate(const std::string &content, const std::string &destinationFile)
{
}

void FileService::copyFiles()
{
}
void FileService::removeFile(const std::string &filePath)
{
    //can't delete file that doesnt exist
    File *target = repository->find(currentDirectory, filePath);
    if (!target)
    {
        throw std::invalid_argument("File does not exist");
    }

    //guard if file is a directory
    Directory *targetDirectory = dynamic_cast<Directory *>(target);
    if (targetDirectory) 
    {
        throw std::invalid_argument("Specified file is a directory");
    }

    Directory * parentDirectory = dynamic_cast<Directory *>(target->getParent());
    parentDirectory->removeFile(target->getName());
    delete target;
}

void FileService::makeDirectory(const std::string &filePath)
{
    if (filePath.size() == 0)
    {
        throw std::invalid_argument("Invalid path specified");
    }

    repository->addDirectory(currentDirectory, filePath);
}

void FileService::removeDirectory(const std::string &filePath)
{
    //can't delete file that doesnt exist
    File *target = repository->find(currentDirectory, filePath);
    if (!target)
    {
        throw std::invalid_argument("Directory does not exist");
    }

    //can't delete file which is not a directory
    Directory *targetDirectory = dynamic_cast<Directory *>(target);
    if (!targetDirectory) 
    {
        throw std::invalid_argument("Specified file is not a directory");
    }

    //can't delete current directory
    if (currentDirectory == targetDirectory)
    {
        throw std::invalid_argument("Invalid argument");
    }

    if (targetDirectory->getSubFiles().size() > 0)
    {
        throw std::invalid_argument("Directory is not empty");
    }

    Directory *parent = targetDirectory->getParent();
    parent->removeFile(targetDirectory->getName());
    delete targetDirectory;
}
void FileService::makeSymbolicLink(const std::string &filePath, const std::string &linkPath)
{
    // std::string fileToLink = filePath;
    // // make filePath absolute
    // if (fileToLink[0] != '/')
    // {
    //     fileToLink = getWorkingDirectory() + "/" + fileToLink;
    // }

    // // check if file at linkPath exists
    // File *linkTarget = repository->find(currentDirectory, linkPath);
    // if (linkTarget)
    // {
    //     throw std::invalid_argument("Destination file already exists");
    // }

    // File * fileTarget = repository->find(currentDirectory, fileToLink);
    // if (fileTarget && fileTarget->getMetaData().fileType == FileType::Directory)
    // {
    //     std::string error = filePath + " is a directory";
    //     throw std::invalid_argument(error);
    // }

    // FileFactory factory = FileFactory();
    // // SymbolicLink * newLink = factory.createSymbolicLink("TODO", linkPath, )
    // // if file exists
    // // // if exists and is dir
}

std::string FileService::getStat(const std::string &path) const
{
    File *target = repository->find(currentDirectory, path);
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