#include "ordinary_file.hpp"
#include <iostream>

OrdinaryFile::OrdinaryFile(const std::string &name, Directory *parent) : File(name, FileType::File)
{
    this->parent = parent;
    content = "";
}

void OrdinaryFile::appendToContent(const std::string &newData)
{
}

void OrdinaryFile::setContent(const std::string &data)
{
}

void OrdinaryFile::getContent() const
{
    // print content
}
