#pragma once
#include <string>
#include "meta_data.cpp"
#include "../../enums/file_type.cpp"

class File
{
protected:
    std::string name;
    MetaData metaData;

    File(const std::string &name, FileType fileType);

public:
    const std::string getName() const;
    const MetaData getMetaData() const;
    virtual const std::string getContent() const = 0;
    virtual File *getParent() const = 0;
    virtual ~File() = default;

    virtual void updateSize() = 0;
    void updateLastAccesDate();
    void updateLastContentModificationDate();
    void updateLastMetaDataModificationDate(); 
};