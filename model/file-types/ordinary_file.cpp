#include "ordinary_file.hpp"
#include <iostream>

OrdinaryFile::OrdinaryFile(const std::string &name, const std::string &content, Directory *parent) : File(name, FileType::File)
{
    this->parent = parent;
    this->content = content;
    parent->addFile(this);
}

OrdinaryFile::OrdinaryFile(const OrdinaryFile &other, Directory *parent) : File(other.name, FileType::File)
{
    this->parent = parent == nullptr ? other.parent : parent;
    content = other.content;
    parent->addFile(this);
}

Directory *OrdinaryFile::getParent() const
{
    return this->parent;
}

const std::string OrdinaryFile::getContent() const
{
    return content;
}
