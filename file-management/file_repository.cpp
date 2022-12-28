#include "file_repository.hpp"

FileRepository::FileRepository()
{
    this->root = new Directory("~", nullptr);
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

void FileRepository::add(File *file, const std::string filePath)
{
    // guard for nullptr
    if (!file)
    {
        throw std::invalid_argument("Null pointer as file reference");
    }

    //guard for existing file
    if (fileExists(filePath))
    {
        throw std::invalid_argument("File already exists");
    }

    // traverse file path and create directories till the end
}

bool FileRepository::fileExists(const std::string &filePath)
{
    if (filePath.size() == 0) {
        return false;
    }

    // traverse from root till invalid file or existing file
}

void FileRepository::remove(const std::string filePath)
{
    if (!fileExists(filePath)) {
        throw std::invalid_argument("File does not exist");
    }

    //traverse from root till the end
    //delete file
}

Directory *FileRepository::getRoot()
{
    return root;
}