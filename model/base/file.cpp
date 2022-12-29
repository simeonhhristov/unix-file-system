#include "file.hpp"
#include "meta_data.cpp"

File::File(const std::string &_name, FileType fileType) : name(_name), metaData(fileType)
{}

File::File(const File &other)
{
    name = other.name + " copy";
    metaData = other.metaData;
}

const std::string File::getName() const
{
    return name;
}

const MetaData File::getMetaData() const
{
    return metaData;
}