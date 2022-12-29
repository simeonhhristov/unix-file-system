#include "ordinary_file.hpp"
#include <iostream>

OrdinaryFile::OrdinaryFile(const std::string &name, Directory *parent) : File(name, FileType::File)
{
    this->parent = parent;
    content = "";
    parent->addFile(this);
}

OrdinaryFile::OrdinaryFile(const OrdinaryFile &other, Directory *parent) : File(other.name + " copy", FileType::File)
{
    this->parent = parent == nullptr ? other.parent : parent;
    content = other.content;
    parent->addFile(this);
}

void OrdinaryFile::appendToContent(const std::string &newData)
{
}

void OrdinaryFile::setContent(const std::string &data)
{
}

Directory *OrdinaryFile::getParent() const
{
    return this->parent;
}

void OrdinaryFile::getContent() const
{
    // print content
}
