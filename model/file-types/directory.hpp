#pragma once
#include <vector>
#include "../base/file.hpp"

class Directory : public File
{
private:
    Directory *parent;
    std::vector<File *> subFiles;

public:
    Directory(const std::string &name, Directory *parent);
    ~Directory();

    void createOrdinaryFile(const std::string &name);
    void createDirectory(const std::string &name);
    void createSymbolicLink(const std::string &name);

    void removeFile(const std::string &name);
    void removeDirectory(const std::string &name);

    virtual void getContent() const;
};