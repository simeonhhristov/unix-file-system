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

    Directory *dir1 = factory.createDirectory("", nullptr);
    Directory *dir2 = factory.createDirectory("child1", dir1);
    Directory *dir3 = factory.createDirectory("child2", dir2);
    Directory *dir4 = factory.createDirectory("child4", dir1);

    OrdinaryFile *file = factory.createOrdinaryFile("file1", "Orignial", dir1);
    OrdinaryFile *file1 = factory.createOrdinaryFile("file1", "testContent", dir2);

    SymbolicLink *link1 = factory.createSymbolicLink("link1", "/child1/file1", dir2);

    dir2->addFile(file1);

    FileRepository *fileRepo = new FileRepository(dir1);
    FileService *fileService = new FileService(fileRepo, dir1);
    DirectoryUtils dirUtil = DirectoryUtils();

    // std::cout << fileService->getWorkingDirectory() << "\n";
    fileService->changeDirectory("child1");
    fileService->createOrdinaryFile("content1", "file2");
    fileService->createOrdinaryFile("content2", "file3");
    std::vector<std::string> paths;
    paths.push_back("child2");
    paths.push_back("file2");
    paths.push_back("file3");
    fileService->copyFiles(paths, "/");
    std::cout << dirUtil.findFile(dir1, "file1")->getName() << "\n";
    std::cout << dirUtil.findFile(dir1, "file2")->getName() << "\n";
    std::cout << dirUtil.findFile(dir1, "file3")->getName() << "\n";
    std::cout << dirUtil.findFile(dir1, "file1 copy")->getName() << "\n";
}