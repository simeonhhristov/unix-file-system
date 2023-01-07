#pragma once
#include "../model/file-types/directory.hpp"
#include "../model/file-types/ordinary_file.hpp"
#include "../model/file-types/symbolic_link.hpp"
#include "file_factory.hpp"

class FileRepository
{
private:
    Directory *root;
    FileFactory fileFactory;

public:
    FileRepository();
    FileRepository(const FileRepository &other) = delete;
    FileRepository &operator=(const FileFactory &other) = delete;
    FileRepository(Directory *root);
    ~FileRepository();

    void addDirectory(Directory *startingDirectory, const std::string filePath);
    void addFile(Directory *startingDirectory, const std::string &data, const std::string &filePath, FileType fileType);
    void copyFile(Directory *startingDirectory, const std::string &fileToCopy, const std::string &destination);
    File *find(Directory *startingDirectory, const std::string &filePath);
    void remove(const std::string filePath);
    Directory *getRoot();
};