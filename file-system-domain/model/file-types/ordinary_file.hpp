#pragma once
#include <string>
#include "../base/file.hpp"
#include "directory.hpp"

class OrdinaryFile : public File
{
private:
    Directory *parent;
    std::string content;

public:
    OrdinaryFile(const std::string &name, const std::string &content, Directory *parent);
    OrdinaryFile(const OrdinaryFile &other, Directory *parent = nullptr);
    OrdinaryFile(const OrdinaryFile &other) = delete;
    Directory *getParent() const;
    virtual const std::string getContent() const;
    virtual void updateSize();
};