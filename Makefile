.PHOPNY: build
build:
	@g++ --std=c++11 main.cpp\
	 utils/id_generator.cpp\
	 utils/directory_utils.cpp\
	 utils/string_utils.cpp\
	 model/base/file.cpp\
	 model/file-types/ordinary_file.cpp\
	 model/file-types/directory.cpp\
	 model/file-types/symbolic_link.cpp\
	 file-management/file_factory.cpp\
	 file-management/file_service.cpp\
	 file-management/file_repository.cpp\