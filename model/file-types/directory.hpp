#pragma once
#include <vector>
#include "../base/file.hpp"

class Directory : public File
{
private:
    Directory *parent;
    std::vector<File *> subFiles;

    friend class DirectoryUtils;

public:
    Directory(const std::string &name, Directory *parent);
    ~Directory();

    void addFile(File* file);

    void removeFile(const std::string &name);
    void removeDirectory(const std::string &name);

    Directory * getParent() const;
    virtual void getContent() const;
};