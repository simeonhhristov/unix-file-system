#pragma once
#include <iostream>
#include "../../enums/file_type.cpp"
#include "../../utils/id_generator.hpp"

struct MetaData
{
    int serialNumber;
    int fileSize;
    FileType fileType;
    unsigned lastAccessDate;
    unsigned lastContentModificationDate;
    unsigned lastMetaDataModificationDate;

    MetaData() {
        serialNumber = 0;
        fileSize = 0;
        fileType = FileType::File;
        lastAccessDate = 0;
        lastContentModificationDate = 0;
        lastMetaDataModificationDate = 0;
    }

    MetaData(FileType fileType)
    {
        this->serialNumber = IdGenerator::shared.generateId();
        this->fileSize = 0;
        this->fileType = fileType;
        this->lastAccessDate = std::time(nullptr);
        this->lastContentModificationDate = std::time(nullptr);
        this->lastMetaDataModificationDate = std::time(nullptr);
    }
};