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

Directory *copyDirectory(Directory *directory)
{
    Directory *copy;
    try
    {
        copy = new Directory(*directory, directory->getParent());
    }
    catch (...)
    {
        return nullptr;
    }
    return copy;
}

OrdinaryFile *copyOrdinaryFile(OrdinaryFile *file)
{
    OrdinaryFile *copy;
    try
    {
        copy = new OrdinaryFile(*file, file->getParent());
    }
    catch (...)
    {
        return nullptr;
    }
    return copy;
}

SymbolicLink *copySymbolicLink(SymbolicLink *symbolicLink)
{
    SymbolicLink *copy;
    try
    {
        copy = new SymbolicLink(*symbolicLink, symbolicLink->getParent());
    }
    catch (...)
    {
        return nullptr;
    }
    return copy;
}