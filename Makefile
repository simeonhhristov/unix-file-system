.PHOPNY: build
build:
	@g++ --std=c++11 main.cpp\
	 utils/id_generator.cpp\
	 model/base/file.cpp\
	 model/file-types/ordinary_file.cpp\
	 model/file-types/directory.cpp\
	 file-management/file_factory.cpp\