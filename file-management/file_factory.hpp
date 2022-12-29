#pragma once
#include "../model/file-types/directory.hpp"
#include "../model/file-types/ordinary_file.hpp"
#include "../model/file-types/symbolic_link.hpp"

class FileFactory
{
public:
    Directory *createDirectory(const std::string &name, Directory *parent);
    OrdinaryFile *createOrdinaryFile(const std::string &name, const std::string &content, Directory *parent);
    SymbolicLink *createSymbolicLink(const std::string &name, const std::string &filePath, Directory *parent);

    Directory *copyDirectory(Directory *directory);
    OrdinaryFile *copyOrdinaryFile(OrdinaryFile *file);
    SymbolicLink *copySymbolicLink(SymbolicLink *symbolicLink);
};