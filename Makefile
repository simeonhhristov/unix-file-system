.PHOPNY: build
build:
	@g++ --std=c++11 main.cpp\
	 file-system-domain/utils/id_generator.cpp\
	 file-system-domain/utils/directory_utils.cpp\
	 file-system-domain/model/base/file.cpp\
	 file-system-domain/model/file-types/ordinary_file.cpp\
	 file-system-domain/model/file-types/directory.cpp\
	 file-system-domain/model/file-types/symbolic_link.cpp\
	 file-system-domain/file-management/file_factory.cpp\
	 file-system-domain/file-management/file_service.cpp\
	 file-system-domain/file-management/file_repository.cpp\
	 file-system-utils/string_utils.cpp\
	 file-system-cli/engine/engine.cpp\
	 file-system-cli/input-handling/input_handler.cpp\