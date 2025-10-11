#pragma once

#include <filesystem>
#include <string>

#include <algorithm>
#include <vector>

namespace fs = std::filesystem;

namespace near {

class FileSource {

protected:
	std::vector<std::string> path_vecs;

public:

	virtual void poll_file() {
		this->path_vecs.emplace_back(this->path.string());
	}

	fs::path path;

	FileSource(): path(".") {}
	FileSource(fs::path p): path(p) {}

	class Iterator {
        std::vector<std::string>::iterator it;

    public:
        Iterator(std::vector<std::string>::iterator init) : it(init) {}

        std::string& operator*() { return *it; }
        Iterator& operator++() { ++it; return *this; }
        bool operator!=(const Iterator& other) const { return it != other.it; }
    };

	Iterator begin() {
		if(this->path_vecs.empty()) this->poll_file();
		return Iterator(this->path_vecs.begin());
	}

	Iterator end() {
		if(this->path_vecs.empty()) this->poll_file();
		return Iterator(this->path_vecs.end());
	}

	void merge(FileSource other) {
		for(std::string path : other) {
			this->path_vecs.emplace_back(path);
		}
	}

};

class FolderFileSource: public FileSource {
private:
	std::vector<std::string> extensions;

	void find_files(const fs::path& path) {
		for(const auto& entry : fs::directory_iterator(path)) {
			if(fs::is_directory(entry)) {
				find_files(entry.path());
			} else if(fs::is_regular_file(entry) && std::find(this->extensions.begin(), this->extensions.end(), entry.path().extension().string()) != this->extensions.end()) {
				this->path_vecs.emplace_back(entry.path().string());
			}
		}
	}

	void poll_file() override {
		if(fs::exists(this->path)) this->find_files(this->path);
	}

public:
	FolderFileSource(): FileSource() {}
	FolderFileSource(fs::path path): FileSource(path) {}
	
	void add_ext(std::string ext) {
		this->extensions.emplace_back(ext);
	}

};

}