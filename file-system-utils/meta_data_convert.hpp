#pragma once
#include <string>
#include "../file-system-domain/enums/file_type.cpp"

namespace metadata_convert {
    std::string convertFileTypeToString(FileType fileType);
    std::string convertUnixTimeStampToString(long timestamp);
}