#include <vector>
#include <string>

#include <near/files.hpp>

namespace near {

class Compiler {
public:
	bool compile_only;
	bool warnings;
	bool extra_warnings;

	int optimization_level;

	bool debug_info;

	std::vector<std::string> include_paths;
	std::vector<std::string> lib_paths;
	std::vector<std::string> libs;

	std::string ref;

	Compiler(std::string ref) {
		this->ref = ref;
		this->compile_only = false;

		this->warnings = false;
		this->extra_warnings = false;
		this->optimization_level = 0;
		this->debug_info = false;
	}

	void add_include_path(std::string path) {
		this->include_paths.emplace_back(path);
	}

	void add_lib_path(std::string path) {
		this->include_paths.emplace_back(path);
	}

	void add_lib(std::string lib) {
		this->libs.emplace_back(lib);
	}

	void debug_settings() {
		this->debug_info = true;
		this->optimization_level = 0;
		this->warnings = true;
		this->extra_warnings = true;
	}

	inline virtual void build(FileSource* source, std::string out);

};


}