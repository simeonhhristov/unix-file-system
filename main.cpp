#include <iostream>
#include "model/base/file.hpp"
#include "model/file-types/ordinary_file.hpp"
#include "model/file-types/directory.hpp"   
#include "model/file-types/symbolic_link.hpp"
#include "file-management/file_factory.hpp"
#include "utils/directory_utils.hpp"

int main()
{
    DirectoryUtils util = DirectoryUtils();
    FileFactory factory = FileFactory();

    Directory *dir1 = factory.createDirectory("", nullptr);
    Directory * dir2 = factory.createDirectory("child1", dir1);
    Directory * dir3 = factory.createDirectory("child2", dir2);
    
    
    
    //std::cout << util.getFullPath(dir3); --done
}