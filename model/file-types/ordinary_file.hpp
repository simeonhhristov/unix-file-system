#pragma once
#include "../base/file.hpp"
#include "directory.hpp"

class OrdinaryFile : public File
{
private:
    Directory *parent;
    std::string content;

public:
    OrdinaryFile(const std::string &name, Directory *parent);

    void appendToContent(const std::string &newData);
    void setContent(const std::string &data);
    virtual void getContent() const;
};