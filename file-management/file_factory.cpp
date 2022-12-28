#include "file_factory.hpp"

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
        newFile = new OrdinaryFile(name, parent);
        newFile->setContent(content);
    }
    catch (...)
    {
        return nullptr;
    }

    return newFile;
}

SymbolicLink *FileFactory::createSymblicLink(const std::string &name, const std::string &filePath, Directory *parent)
{
    SymbolicLink *newLink;
    try
    {
        newLink = new SymbolicLink(name, parent, filePath);
    }
    catch (const std::exception &e)
    {
        return nullptr;
    }
    return newLink;
}