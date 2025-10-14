#include <near/file.hpp>

using namespace near;

FileStream::FileStream(fs::path dir) {
	this->directories.push_back(dir);
}

void FileStream::add_directory(fs::path dir) {
	this->directories.push_back(dir);

	for(std::string ext : this->extensions) {
		this->collect_ext_in_path(dir, ext);
	}
}

void FileStream::add_file(fs::path file) {
	this->paths.push_back(file);
}

void FileStream::add_file_extension(std::string extension) {
	this->extensions.push_back(extension);

	for(fs::path path : this->directories) {
		this->collect_ext_in_path(path, extension);
	}
}
