#include <string>
#include "symbolic_link.hpp"

SymbolicLink::SymbolicLink(const std::string &name, const std::string &filePath, Directory *parent) : File(name, FileType::Symlink)
{
    this->parent = parent;
    this->filePath = filePath;
    metaData.fileSize = filePath.size();
    parent->addFile(this);
}

Directory *SymbolicLink::getParent() const
{
    return parent;
}

const std::string SymbolicLink::getContent() const
{
    return filePath;
}

void SymbolicLink::updateSize()
{
    metaData.fileSize = filePath.size();
    updateLastMetaDataModificationDate();
    parent->updateSize();
}