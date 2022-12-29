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

void Directory::addFile(File *file)
{
    // guard for nullptr
    if (!file)
    {
        return;
    }

    // guard for existing file
    for (int i = 0; i < subFiles.size(); i++)
    {
        if (subFiles[i]->getName() == file->getName())
        {
            return;
        }
    }

    subFiles.push_back(file);
}

void Directory::removeFile(const std::string &name)
{
}

void Directory::removeDirectory(const std::string &name)
{
}

Directory *Directory::getParent() const
{
    return parent;
}

void Directory::getContent() const
{
    // print names of subfiles
}