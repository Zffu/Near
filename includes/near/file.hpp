#pragma once

#include <filesystem>
#include <string>

#include <vector>

#include <utils/iterator.hpp>

namespace fs = std::filesystem;

namespace near::io {

class FileStream {
protected:
	std::vector<fs::path> paths;

public:
	std::vector<fs::path> directories;

	FileStream();
	FileStream(fs::path dir);

	VecIterator<fs::path> begin() {
		return VecIterator<fs::path>(this->paths.begin());
	}

	VecIterator<fs::path> end() {
		return VecIterator<fs::path>(this->paths.end());
	}
};


}