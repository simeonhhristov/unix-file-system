#include <string>
#include "symbolic_link.hpp"

SymbolicLink::SymbolicLink(const std::string &name, Directory *parent, const std::string &filePath) : File(name, FileType::Symlink)
{
    this->parent = parent;
    this->filePath = filePath;
}

void SymbolicLink::changeLink(const std::string &newPath)
{
}

void SymbolicLink::getContent() const
{
    // show contents of file at path
}