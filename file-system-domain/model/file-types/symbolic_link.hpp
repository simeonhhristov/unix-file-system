#pragma once
#include <string>
#include "../base/file.hpp"
#include "directory.hpp"

class SymbolicLink : public File
{
private:
    Directory *parent;
    std::string filePath;

public:
    SymbolicLink(const std::string &name, const std::string &filePath, Directory *Parent);
    SymbolicLink(const SymbolicLink &other) = delete;
    Directory *getParent() const;
    virtual const std::string getContent() const;
    virtual void updateSize();
};
