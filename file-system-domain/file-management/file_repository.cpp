#include "file_repository.hpp"
#include "../utils/directory_utils.hpp"
#include "../../file-system-utils/error_constants.hpp"

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
        std::string error = filePath + errors::DIRECTORY_ALREADY_EXISTS;
        throw std::invalid_argument(error);
    }

    DirectoryUtils directoryUtils = DirectoryUtils();
    directoryUtils.createDirectory(startingDirectory, filePath);
}

void FileRepository::addFile(Directory *startingDirectory, const std::string &data, const std::string &filePath, FileType fileType)
{
    if (find(startingDirectory, filePath))
    {
        std::string error = filePath + errors::FILE_ALREADY_EXISTS;
        throw std::invalid_argument(error);
    }

    DirectoryUtils directoryUtils = DirectoryUtils();
    directoryUtils.createFile(startingDirectory, filePath, data, fileType);
}

void FileRepository::copyFile(Directory *startingDirectory, const std::string &fileToCopy, const std::string &destinationPath)
{
    File *target = find(startingDirectory, fileToCopy);
    if (!target)
    {
        std::string error = fileToCopy + errors::FILE_DOES_NOT_EXIST;
        throw std::invalid_argument(error);
    }

    if (target->getMetaData().fileType == FileType::Directory)
    {
        std::string error = fileToCopy + errors::FILE_IS_DIRECTORY;
        throw std::invalid_argument(error);
    }

    DirectoryUtils directoryUtils = DirectoryUtils();
    if (target->getMetaData().fileType == FileType::Symlink)
    {
        target->updateLastAccesDate();
        target = directoryUtils.getFileFromSymLink(startingDirectory, target->getContent());
    }

    Directory *destination = directoryUtils.findDirectory(startingDirectory, destinationPath);
    if (!destination)
    {
        std::string error = destinationPath + errors::DIRECTORY_DOES_NOT_EXIST;
        throw std::runtime_error(error);
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
    
    target->updateLastAccesDate();
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
        std::string error = filePath + errors::FILE_DOES_NOT_EXIST;
        throw std::invalid_argument(error);
    }

    // traverse from root till the end
    // delete file
}

Directory *FileRepository::getRoot()
{
    return root;
}