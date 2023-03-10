#include <string>
#include "directory.hpp"
#include "ordinary_file.hpp"
#include "../base/file.hpp"
#include "../../enums/file_type.cpp"

OrdinaryFile::OrdinaryFile(const std::string &name, const std::string &content, Directory *parent) : File(name, FileType::File)
{
    this->parent = parent;
    this->content = content;
    metaData.fileSize = content.size();
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

void OrdinaryFile::updateSize()
{
    metaData.fileSize = content.size();
    updateLastMetaDataModificationDate();
    parent->updateSize();
}