#include <vector>
#include <string>
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
    updateSize();
    updateLastContentModificationDate();
}

void Directory::removeFile(const std::string &name)
{
    for (int i = 0; i < subFiles.size(); i++)
    {
        if (name == subFiles[i]->getName())
        {
            subFiles.erase(subFiles.begin() + i);
            break;
        }
    }
    updateSize();
    updateLastContentModificationDate();
}

Directory *Directory::getParent() const
{
    return parent;
}

const std::vector<File *> &Directory::getSubFiles() const
{
    return subFiles;
}

const std::string Directory::getContent() const
{
    std::string result = "";
    for (int i = 0; i < subFiles.size(); i++)
    {
        result += subFiles[i]->getName() + " ";
    }

    return result;
}

void Directory::updateSize()
{
    int newSize = 0;
    for (size_t i = 0; i < subFiles.size(); i++)
    {
        newSize += subFiles[i]->getMetaData().fileSize;
    }
    metaData.fileSize = newSize;
    updateLastMetaDataModificationDate();

    // recursively update all predecessors' size
    if (parent)
    {
       parent->updateSize();
    }
}