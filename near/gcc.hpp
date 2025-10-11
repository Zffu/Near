#pragma once

#include <near/compiler.hpp>

#include <cstdlib>

namespace near::compilers {

enum GCCOptimizationLevel {
	O_ZERO = 0,
	O_ONE = 1,
	O_TWO = 2,
	O_THREE = 3,
	O_S = 4,
	O_FAST = 5
};

class GCCCompiler: public Compiler {
public:	
	GCCCompiler(std::string reference): Compiler(reference) {}

	inline void build_unlinked(FileSource* source, CompilerOutput* output) {
		this->compile_only = true;
		this->build_normal(source, output);
	}

	inline void build(FileSource* source, CompilerOutput* output) {
		if(output->type == EXECUTABLE) {
			this->build_normal(source, output);
			return;
		}

		if(output->type == STATIC_LIB) {
			this->build_unlinked(source, output);
			
			std::string command = "ar ";

			if(this->archive_insert_files) command += "r";
			if(this->archive_create_if_not_exists) command += "c";
			if(this->archive_index) command += "s";

			std::vector<fs::path> objects;

			for(const auto& inpath : *source) {
				fs::path objpath = inpath.filename();
				objpath.replace_extension(".o");

				objects.push_back(objpath);
			}

			command += " " + output->get_file_name();
			
			for(fs::path path : objects) {
				command += " " + path.string();
			}

			this->run_command(command);

			if(this->clean_object_files) {
				std::cout << "Info: cleaning build files!";

				for(fs::path path : objects) {
					if(fs::exists(path)) fs::remove(path);
				}
			}

			return;
		}

		if(output->type == DYNAMIC_LIB) {
			this->position_independant = true;
			this->build_unlinked(source, output);

			std::vector<fs::path> objects;

			for(const auto& inpath : *source) {
				fs::path objpath = inpath.filename();
				objpath.replace_extension(".o");
				
				objects.push_back(objpath);
			}

			std::string command = "gcc -shared -o " + output->get_file_name();

			for(fs::path path : objects) {
				command += " " + path.string();
			}

			this->run_command(command);

			if(this->clean_object_files) {
				std::cout << "Info: cleaning build files!";

				for(fs::path path : objects) {
					if(fs::exists(path)) fs::remove(path);
				}
			}
		}


	}

	inline void optimized_settings() override {
		this->optimization_level = 3;
		this->debug_info = false;
		this->archive_index = true;
	}

	inline void build_normal(FileSource* source, CompilerOutput* output) {
		std::string command = "gcc";

		if(this->compile_only) command += " -c";
		else command += " -o " + output->get_file_name();

		if(this->warnings) command += " -Wall";
		if(this->extra_warnings) command += " -Wextra";
		if(this->position_independant) command += " -fPIC";

		std::string levels[] = {" -O0", " -O1", " -O2", " -O3", " -Os", " -Ofast"};

		if(this->optimization_level > 5) this->optimization_level = 5;
		if(this->optimization_level < 0) this->optimization_level = 0;

		command += levels[this->optimization_level];

		if(this->debug_info) command += " -g";

		for(std::string path : this->include_paths) {
			command += " -I" + path;
		}

		for(std::string path : this->lib_paths) {
			command += " -L" + path;
		}

		for(std::string lib : this->libs) {
			command += " -I" + lib;
		}

		command += " -std=" + this->ref;

		source->poll_file();

		for(fs::path path : *source) {
			command += " " + path.string();
		}

		this->run_command(command);
	}


};

}