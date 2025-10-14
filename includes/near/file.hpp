#pragma once

#include <filesystem>
#include <string>

#include <vector>

#include <utils/iterator.hpp>

namespace fs = std::filesystem;

namespace near {

class FileStream {
protected:
	std::vector<fs::path> paths;
	std::vector<std::string> extensions;

	void collect_ext_in_path(fs::path path, std::string ext);

public:
	std::vector<fs::path> directories;

	FileStream() {};
	FileStream(fs::path dir);

	void add_directory(fs::path dir);
	void add_file(fs::path file);

	void add_file_extension(std::string extension);

	VecIterator<fs::path> begin() {
		return VecIterator<fs::path>(this->paths.begin());
	}

	VecIterator<fs::path> end() {
		return VecIterator<fs::path>(this->paths.end());
	}
};


}