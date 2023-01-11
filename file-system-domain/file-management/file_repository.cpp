#include "file_repository.hpp"
#include "../utils/directory_utils.hpp"

FileRepository::FileRepository()
{
    this->root = new Directory("", nullptr);
    fileFactory = FileFactory();
}

FileRepository::FileRepository(Directory *root)
{
    this->root = root;
    fileFactory = FileFactory();
}

FileRepository::~FileRepository()
{
    delete root;
}

void FileRepository::addDirectory(Directory *startingDirectory, const std::string filePath)
{
    // guard for existing file
    if (find(startingDirectory, filePath))
    {
        throw std::invalid_argument("File already exists");
    }

    DirectoryUtils directoryUtils = DirectoryUtils();
    directoryUtils.createDirectory(startingDirectory, filePath);
}

void FileRepository::addFile(Directory *startingDirectory, const std::string &data, const std::string &filePath, FileType fileType)
{
    if(find(startingDirectory, filePath))
    {
        throw std::invalid_argument("File already exists");
    }

    DirectoryUtils directoryUtils = DirectoryUtils();
    directoryUtils.createFile(startingDirectory, filePath, data, fileType);
}

void FileRepository::copyFile(Directory *startingDirectory, const std::string &fileToCopy, const std::string &destinationPath)
{
    File *target = find(startingDirectory, fileToCopy);
    if(!target)
    {
        throw std::invalid_argument("File does not exist");
    }

    if(target->getMetaData().fileType == FileType::Directory)
    {
        throw std::invalid_argument("File is a directory (not copied)");
    }

    DirectoryUtils directoryUtils = DirectoryUtils();
    if(target->getMetaData().fileType == FileType::Symlink)
    {
        target = directoryUtils.getFileFromSymLink(startingDirectory, target->getContent());
    }

    Directory * destination = directoryUtils.findDirectory(startingDirectory, destinationPath);
    if(!destination)
    {
        throw std::runtime_error("Destination directory does not exist");
    }
    
    std::vector<File *> subFiles = destination->getSubFiles();
    for (int i = 0; i < subFiles.size(); i++)
    {
        if (subFiles[i]->getName() == target->getName())
        {
            std::string copyName = directoryUtils.createFileCopyName(destination, target->getName());
            addFile(destination, target->getContent(), copyName, target->getMetaData().fileType);
            return;
        }
    }

    addFile(destination, target->getContent(), target->getName(), target->getMetaData().fileType);
}

File *FileRepository::find(Directory *startingDirectory, const std::string &filePath)
{
    if (filePath.size() == 0)
    {
        return nullptr;
    }

    DirectoryUtils directoryUtils = DirectoryUtils();
    File *target = directoryUtils.findFile(startingDirectory, filePath);
    if (!target)
    {
        target = directoryUtils.findDirectory(startingDirectory, filePath);
    }
    return target;
}

void FileRepository::remove(const std::string filePath)
{
    if (!find(nullptr, filePath))
    {
        throw std::invalid_argument("File does not exist");
    }

    // traverse from root till the end
    // delete file
}

Directory *FileRepository::getRoot()
{
    return root;
}