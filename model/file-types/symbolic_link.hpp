#pragma once
#include <string>
#include "../base/file.hpp"
#include "directory.hpp"

class SymbolicLink : public File
{
private:
    Directory* parent;
    std::string filePath;

public:
    SymbolicLink(const std::string &name, Directory *parent, const std::string &filePath);

    void changeLink(const std::string &newPath);
    virtual void getContent() const;
};
