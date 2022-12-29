#include <vector>
#include "directory.hpp"
#include "ordinary_file.hpp"
#include "symbolic_link.hpp"

Directory::Directory(const std::string &name, Directory *parent) : File(name, FileType::Directory)
{
    this->parent = parent;
    subFiles = std::vector<File *>();
    if (parent)
    {
        parent->addFile(this);
    }
}

Directory::Directory(const Directory &other, Directory *parent) : File(other)
{
    this->parent = parent == nullptr ? other.parent : parent;
    name = parent == nullptr ? name : other.name;
    
    for (int i = 0; i < other.subFiles.size(); i++)
    {
        switch (other.subFiles[i]->getMetaData().fileType)
        {
        case FileType::Directory:
        {
            Directory *newDirectory = new Directory(*dynamic_cast<Directory *>(other.subFiles[i]), this);
            subFiles.push_back(newDirectory);
            break;
        }
        case FileType::File:
        {
            OrdinaryFile *newFile = new OrdinaryFile(*dynamic_cast<OrdinaryFile *>(other.subFiles[i]), this);
            subFiles.push_back(newFile);
            break;
        }
        case FileType::Symlink:
        {
            SymbolicLink *newLink = new SymbolicLink(*dynamic_cast<SymbolicLink *>(other.subFiles[i]), this);
            subFiles.push_back(newLink);
            break;
        }
        }
    }
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