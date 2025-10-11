#include <filesystem>
#include <string>

#include <vector>

namespace near {

class FileSource {
private:
	std::vector<std::string> path_vecs;

public:
	std::string path;

	FileSource(): path(".") {}
	FileSource(std::string p): path(p) {}

	class Iterator {
        std::vector<std::string>::iterator it;

    public:
        Iterator(std::vector<std::string>::iterator init) : it(init) {}

        std::string& operator*() { return *it; }
        Iterator& operator++() { ++it; return *this; }
        bool operator!=(const Iterator& other) const { return it != other.it; }
    };

	Iterator begin() {
		return Iterator(this->path_vecs.begin());
	}

	Iterator end() {
		return Iterator(this->path_vecs.end());
	}
};

}