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

void FileRepository::addDirectory(Directory* startingDirectory, const std::string filePath)
{
    // guard for existing file
    if (find(startingDirectory, filePath))
    {
        throw std::invalid_argument("File already exists");
    }

    DirectoryUtils directoryUtils = DirectoryUtils();
    directoryUtils.createDirectory(startingDirectory, filePath);
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