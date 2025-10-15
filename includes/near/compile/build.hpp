#include <vector>
#include <string>

#include <near/file.hpp>

namespace near {

class NearBuildInstance {
public:
	static NearBuildInstance* current;

	std::vector<fs::path> build_files;
	FileStream inputStream;

	bool active;

	NearBuildInstance() {
		NearBuildInstance::current = this;
		this->active = true;
	}

	void fail_build(std::string reason);
	void finish_build();

};

}