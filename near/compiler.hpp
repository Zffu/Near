#pragma once

#include <vector>
#include <string>

#include <near/files.hpp>

namespace near {

enum OutputType {
	EXECUTABLE,
	STATIC_LIB,
	DYNAMIC_LIB
};

static fs::path to_object_file(fs::path p) {
	fs::path path = p;
	p.replace_extension(".o");

	return p;
}

static fs::path to_object_file_non_singleton(fs::path p) {
	fs::path path = p.filename();
	path.replace_extension(".o");

	return p;
}

class CompilerOutput {
public:
	std::string name;
	OutputType type;

	CompilerOutput(std::string n, OutputType type): name(n) {
		this->type = type;
	}

	inline std::string get_file_name() {
		if(this->type == STATIC_LIB) return this->name + ".a";
#ifdef _WIN32
		switch(this->type) {
			case EXECUTABLE:
				return this->name + ".exe";
			case DYNAMIC_LIB:
				return this->name + ".dll";	
		}
#else
		switch(this->type) {
			case EXECUTABLE:
				return this->name;
			case DYNAMIC_LIB:
				return this->name + ".so";
		}
#endif
	}

};

class Compiler {
protected:
	bool run_command(std::string cmd) {
		std::cout << "Running command: " << cmd;
		int res = system(cmd.c_str());

#ifdef _WIN32	
		return res == 0;
#else
		return WIFEXITED(res) && WEXITSTATUS(res) == 0;
#endif
	}

	void fail_build() {
		std::cout << "Build failed!";
	}

	std::vector<fs::path> build_files;

public:
	bool compile_only;

	bool clean_object_files;

	bool warnings;
	bool extra_warnings;

	int optimization_level;

	bool archive_insert_files;
	bool archive_create_if_not_exists;
	bool archive_index;

	bool position_independant;

	bool use_singleton_building;

	bool debug_info;

	std::vector<std::string> include_paths;
	std::vector<std::string> lib_paths;
	std::vector<std::string> libs;

	FileSource* compile_against_libs;

	std::string ref;

	Compiler(std::string ref) {
		this->ref = ref;
		this->compile_only = false;

		this->clean_object_files = true;

		this->warnings = false;
		this->extra_warnings = false;
		this->optimization_level = 0;
		this->debug_info = false;

		this->archive_insert_files = true;
		this->archive_create_if_not_exists = true;
		this->archive_index = true;

		this->use_singleton_building = false;

		this->position_independant = false;

		this->compile_against_libs = nullptr;
	}

	void add_include_path(std::string path) {
		this->include_paths.emplace_back(path);
	}

	void add_lib_path(std::string path) {
		this->include_paths.emplace_back(path);
	}

	void bind_libs(FileSource* source) {
		this->compile_against_libs = source;
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

	void post_build() {
		if(this->clean_object_files) {
			std::cout << "INFO: Cleaning build files!";
			
			for(fs::path p : this->build_files) {
				if(fs::exists(p)) fs::remove(p);
			}
		}
	}

	inline virtual void optimized_settings() {

	}

	inline virtual void build(FileSource* source, std::string out) {}

	

};


}