#include "file_factory.hpp"
#include "../model/file-types/directory.hpp"
#include "../model/file-types/ordinary_file.hpp"
#include "../model/file-types/symbolic_link.hpp"

Directory *FileFactory::createDirectory(const std::string &name, Directory *parent)
{
    Directory *newDirectory;
    try
    {
        newDirectory = new Directory(name, parent);
    }
    catch (...)
    {
        return nullptr;
    }

    return newDirectory;
}

OrdinaryFile *FileFactory::createOrdinaryFile(const std::string &name, const std::string &content, Directory *parent)
{
    OrdinaryFile *newFile;
    try
    {
        newFile = new OrdinaryFile(name, content, parent);
    }
    catch (...)
    {
        return nullptr;
    }

    return newFile;
}

SymbolicLink *FileFactory::createSymbolicLink(const std::string &name, const std::string &filePath, Directory *parent)
{
    SymbolicLink *newLink;
    try
    {
        newLink = new SymbolicLink(name, filePath, parent);
    }
    catch (...)
    {
        return nullptr;
    }
    return newLink;
}