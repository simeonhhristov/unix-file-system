#include "file.hpp"
#include "meta_data.cpp"

File::File(const std::string &_name, FileType fileType) : name(_name), metaData(fileType)
{
}

File::File(const File &other)
{
    name = other.name + " copy";
    metaData = other.metaData;
}
void File::changeName(const std::string &newName)
{
    if (newName.size() != 0)
    {
        name = newName;
    }
}

const std::string File::getName() const
{
    return name;
}

const MetaData File::getMetaData() const
{
    return metaData;
}

void File::updateLastAccesDate()
{
    metaData.lastAccessDate = std::time(nullptr);
    updateLastMetaDataModificationDate();
}

void File::updateLastContentModificationDate()
{
    metaData.lastContentModificationDate = std::time(nullptr);
    updateLastMetaDataModificationDate();
}

void File::updateLastMetaDataModificationDate()
{
    metaData.lastMetaDataModificationDate = std::time(nullptr);
}