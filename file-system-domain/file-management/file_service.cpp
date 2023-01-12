#include <vector>
#include <string>
#include <iostream>
#include "file_service.hpp"
#include "../../file-system-utils/error_constants.hpp"
#include "../../file-system-utils/string_utils.hpp"
#include "../../file-system-utils/meta_data_convert.hpp"

FileService::FileService()
{
    currentDirectory = new Directory("", nullptr);
    repository = new FileRepository(currentDirectory);
    directoryUtils = DirectoryUtils();
    stringUtils = StringUtils();
}

FileService::~FileService()
{
    delete repository;
    delete currentDirectory;
}

std::string FileService::getWorkingDirectory() const
{
    return directoryUtils.getFullPath(currentDirectory);
}

std::string FileService::changeDirectory(const std::string &path)
{
    Directory *result = directoryUtils.findDirectory(currentDirectory, path);

    if (!result)
    {
        std::string error = path + errors::DIRECTORY_DOES_NOT_EXIST;
        throw std::invalid_argument(error);
    }

    currentDirectory = result;
    currentDirectory->updateLastAccesDate();
    return result->getName();
}

std::string FileService::getContentsList(const std::string &path) const
{
    Directory *target = directoryUtils.findDirectory(currentDirectory, path);
    std::string result;

    if (!target)
    {
        std::string error = path + errors::DIRECTORY_DOES_NOT_EXIST;
        throw std::invalid_argument(error);
    }

    target->updateLastAccesDate();
    result = target->getContent();
    return result;
}

void FileService::concatenate(const std::vector<std::string> &filePaths, const std::string &destinationFile)
{
    if (repository->find(currentDirectory, destinationFile))
    {
        std::string error = destinationFile + errors::FILE_ALREADY_EXISTS;
        throw std::invalid_argument(error);
    }

    std::string combinedContent = getConcatenatedContents(filePaths);
    createOrdinaryFile(combinedContent, destinationFile);
}

void FileService::createOrdinaryFile(const std::string &content, const std::string &destinationFile)
{
    if (destinationFile.size() == 0)
    {
        throw std::invalid_argument(errors::NOT_SPECIFIED_FILE);
    }
    repository->addFile(currentDirectory, content, destinationFile, FileType::File);
}

std::string FileService::getConcatenatedContents(const std::vector<std::string> &filePaths)
{
    std::string combinedContent = "";
    for (int i = 0; i < filePaths.size(); i++)
    {
        File *target = repository->find(currentDirectory, filePaths[i]);
        if (!target)
        {
            std::string error = filePaths[i] + errors::FILE_DOES_NOT_EXIST;
            throw std::invalid_argument(error);
        }

        if (target->getMetaData().fileType == FileType::Symlink)
        {
            target = directoryUtils.getFileFromSymLink(currentDirectory, target->getContent());
        }

        OrdinaryFile *currentFile = dynamic_cast<OrdinaryFile *>(target);
        if (!currentFile)
        {
            std::string error = filePaths[i] + errors::FILE_NOT_ORDINARY;
            throw std::invalid_argument(error);
        }
        
        currentFile->updateLastAccesDate();
        combinedContent += currentFile->getContent();
    }
    return combinedContent;
}

void FileService::copyFiles(const std::vector<std::string> &filePaths, const std::string &destinationPath)
{
    if (destinationPath.size() == 0)
    {
        throw std::invalid_argument(errors::NOT_SPECIFIED_DESTINATION);
    }

    for (int i = 0; i < filePaths.size(); i++)
    {
        try
        {
            repository->copyFile(currentDirectory, filePaths[i], destinationPath);
        }
        catch (const std::runtime_error &e)
        {
            // rethrow to cancel copy loop
            throw e;
        }
    }
}

void FileService::removeFile(const std::string &filePath)
{
    File *target = repository->find(currentDirectory, filePath);
    if (!target)
    {
        std::string error = filePath + errors::FILE_DOES_NOT_EXIST;
        throw std::invalid_argument(error);
    }

    // guard if file is a directory
    Directory *targetDirectory = dynamic_cast<Directory *>(target);
    if (targetDirectory)
    {
        std::string error = filePath + errors::FILE_IS_DIRECTORY;
        throw std::invalid_argument(error);
    }

    Directory *parentDirectory = dynamic_cast<Directory *>(target->getParent());
    parentDirectory->removeFile(target->getName());
    delete target;
}

void FileService::makeDirectory(const std::string &filePath)
{
    if (filePath.size() == 0)
    {
        std::string error = filePath + errors::INVALID_PATH;
        throw std::invalid_argument(error);
    }

    repository->addDirectory(currentDirectory, filePath);
}

void FileService::removeDirectory(const std::string &filePath)
{
    // can't delete file that doesnt exist
    File *target = repository->find(currentDirectory, filePath);
    if (!target)
    {
        std::string error = filePath + errors::DIRECTORY_DOES_NOT_EXIST;
        throw std::invalid_argument(error);
    }

    // can't delete file which is not a directory
    Directory *targetDirectory = dynamic_cast<Directory *>(target);
    if (!targetDirectory)
    {
        std::string error = filePath + errors::FILE_NOT_DIRECTORY;
        throw std::invalid_argument(error);
    }

    // can't delete current directory
    if (currentDirectory == targetDirectory)
    {
        throw std::invalid_argument(errors::CANT_DELETE_CURRENT_DIR);
    }

    if (targetDirectory->getSubFiles().size() > 0)
    {
        std::string error = filePath + errors::DIR_IS_NOT_EMPTY;
        throw std::invalid_argument(error);
    }

    Directory *parent = targetDirectory->getParent();
    parent->removeFile(targetDirectory->getName());
    delete targetDirectory;
}

void FileService::makeSymbolicLink(const std::string &targetPath, const std::string &linkLocation)
{
    std::string fileToLink = targetPath;
    // make filePath absolute
    if (fileToLink[0] != '/')
    {
        // avoid double '/' at start if currentDirectory is root
        std::string rootPath = getWorkingDirectory();
        rootPath = (rootPath == "/" ? "" : rootPath);
        fileToLink = rootPath + "/" + fileToLink;
    }

    // check if requested to link file is a directory
    File *fileTarget = repository->find(currentDirectory, fileToLink);
    if (fileTarget && fileTarget->getMetaData().fileType == FileType::Directory)
    {
        std::string error = targetPath + errors::FILE_IS_DIRECTORY;
        throw std::invalid_argument(error);
    }

    // determine name of targeted file
    std::string targetFileName = stringUtils.getLastAfter(fileToLink, "/");

    std::string newFilePath = linkLocation.size() == 0 ? targetFileName : linkLocation;
    repository->addFile(currentDirectory, fileToLink, newFilePath, FileType::Symlink);
}

std::string FileService::getStat(const std::string &path) const
{
    File *target = repository->find(currentDirectory, path);
    if (!target)
    {
        throw std::invalid_argument(errors::NO_SUCH_FILE_OR_DIR);
    }

    // no meta data update should be invoced from stat
    MetaData data = target->getMetaData();
    std::string result;
    result += "Size: " + std::to_string(data.fileSize);
    result += ", Type: " + metadata_convert::convertFileTypeToString(data.fileType);
    result += ", Last Modification: " + metadata_convert::convertUnixTimeStampToString(data.lastContentModificationDate);
    result += ", Last Access: " + metadata_convert::convertUnixTimeStampToString(data.lastAccessDate);
    result += ", Last Meta Data Modification: " + metadata_convert::convertUnixTimeStampToString(data.lastMetaDataModificationDate);
    result += ", SerialNo.:" + std::to_string(data.serialNumber);

    return result;
}