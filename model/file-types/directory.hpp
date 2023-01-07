#pragma once
#include <vector>
#include <iostream>
#include "../base/file.hpp"

class Directory : public File
{
private:
    Directory *parent;
    std::vector<File *> subFiles;

public:
    Directory(const std::string &name, Directory *parent);
    Directory(const Directory &other, Directory *parent = nullptr);
    Directory& operator=(const Directory &other) = delete;
    ~Directory();

    void addFile(File* file);
    void removeFile(const std::string &name);
    const std::vector<File *> &getSubFiles() const;
    Directory * getParent() const;
    virtual const std::string& getContent() const;
};