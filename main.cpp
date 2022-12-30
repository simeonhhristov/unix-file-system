#include <iostream>
#include "model/base/file.hpp"
#include "model/file-types/ordinary_file.hpp"
#include "model/file-types/directory.hpp"
#include "model/file-types/symbolic_link.hpp"
#include "file-management/file_factory.hpp"
#include "file-management/file_service.hpp"
#include "utils/directory_utils.hpp"

int main()
{
    DirectoryUtils util = DirectoryUtils();
    FileFactory factory = FileFactory();

    Directory *dir1 = factory.createDirectory("1", nullptr);
    Directory *dir2 = factory.createDirectory("child1", dir1);
    Directory *dir3 = factory.createDirectory("child2", dir2);
    Directory *dir4 = factory.createDirectory("child4", dir1);
    
    OrdinaryFile *file1 = factory.createOrdinaryFile("file1", "testContent", dir2);
    
    SymbolicLink *link1 = factory.createSymbolicLink("link1", "/child1/file1", dir2);
    
    dir2->addFile(file1);

    FileRepository *fileRepo = new FileRepository(dir1);
    FileService *fileService = new FileService(fileRepo, dir1);
    DirectoryUtils dirUtil = DirectoryUtils();

    std::cout << fileService->getStat("child");
}