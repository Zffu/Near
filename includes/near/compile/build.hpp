#include <vector>
#include <string>

#include <near/file.hpp>

namespace near {

class NearBuildInstance {
public:
	std::vector<fs::path> build_files;
	bool active;

	NearBuildInstance() {
		this->active = true;
	}

	void fail_build(std::string reason);
	void finish_build();

};

}