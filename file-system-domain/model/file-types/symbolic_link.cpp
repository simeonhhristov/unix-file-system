#include <string>
#include "symbolic_link.hpp"

SymbolicLink::SymbolicLink(const std::string &name, const std::string &filePath, Directory *parent) : File(name, FileType::Symlink)
{
    this->parent = parent;
    this->filePath = filePath;
    parent->addFile(this);
}
SymbolicLink::SymbolicLink(const SymbolicLink &other, Directory *parent) : File(other)
{
    this->parent = parent == nullptr ? other.parent : parent;
    filePath = other.filePath;
    parent->addFile(this);
}

void SymbolicLink::changeLink(const std::string &newPath)
{
}

Directory *SymbolicLink::getParent() const
{
    return parent;
}

const std::string SymbolicLink::getContent() const
{
    return filePath;
}