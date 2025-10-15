#include <near/file.hpp>

#include <string>

namespace near {

enum CompilerTargetType {
	EXECUTABLE,
	OBJECT_FILE,
	DYNAMIC_LIB,
	STATIC_LIB
};

class CompilerTarget {
public:
	std::string name;
	CompilerTargetType type;

	CompilerTarget(std::string n, CompilerTargetType type): name(n) {
		this->type = type;
	}

	inline std::string get_file_name();
};

class MultiFileCompilerTarget {
private:
	fs::path out_folder;
	CompilerTargetType type;

public:
	MultiFileCompilerTarget(fs::path out_folder, CompilerTargetType type) {
		this->out_folder = out_folder;
		this->type = type;
	}

	fs::path get_out_destination(fs::path file);
};

}