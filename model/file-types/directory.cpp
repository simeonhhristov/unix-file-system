#include <vector>
#include "directory.hpp"

Directory::Directory(const std::string &name, Directory *parent) : File(name, FileType::Directory)
{
    this->parent = parent;
    subFiles = std::vector<File *>();
}

Directory::~Directory()
{
    for (int i = 0; i < subFiles.size(); i++)
    {
        delete subFiles[i];
    }
    subFiles.clear();
}

void Directory::createDirectory(const std::string &name)
{
}

void Directory::createOrdinaryFile(const std::string &name)
{
}

void Directory::createSymbolicLink(const std::string &name)
{
}

void Directory::removeFile(const std::string &name)
{
}

void Directory::removeDirectory(const std::string &name)
{
}

void Directory::getContent() const
{
    // print names of subfiles
}