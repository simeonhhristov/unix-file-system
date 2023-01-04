#pragma once
#include "meta_data.cpp"
#include <string>

class File {
protected:
    std::string name;
    MetaData metaData;

    File(const std::string &name, FileType fileType);
    File(const File &other);
public:
    const std::string getName() const;
    const MetaData getMetaData() const;
    virtual void getContent() const = 0;
    virtual File *getParent() const = 0;
    virtual ~File() = default;
}; 