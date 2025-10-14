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
protected:
	bool useCPP;

public:	
	GCCCompiler(std::string reference, bool useCplusplus = false): Compiler(reference) {
		this->useCPP = useCplusplus;
	}

	inline bool build_unlinked(FileSource* source, CompilerOutput* output) {
		this->compile_only = true;
		
		if(this->use_singleton_building) {
			for(fs::path p : *source) {
				if(p.extension().string() == ".o") continue;
				
				fs::path obj = to_object_file(p);

				this->build_files.push_back(obj);

				FileSource source(p);

				if(!this->build_singular(&source, obj)) {
					return false;
				}
			}
			return true;
		}

		for(fs::path p : *source) {
			this->build_files.push_back(to_object_file_non_singleton(p));
		}

		if(!this->build_outputless(source)) {
			return false;
		}

		return true;
	}

	inline std::string prepare_build_command(FileSource* source) {
		source->poll_file();

		std::string command = (this->useCPP ? "g++" : "gcc");

		if(this->compile_only) command += " -c";
	
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

		for(fs::path path : *source) {
			command += " " + path.string();
		}

		return command;
	}

	inline void build(FileSource* source, CompilerOutput* output) {
		
		if(output->type == EXECUTABLE) {
			if(!this->build_normal(source, output)) {
				this->fail_build();
				return;
			}

			this->post_build();
			return;
		}

		if(output->type == STATIC_LIB) {
			if(!this->build_unlinked(source, output)) {
				this->fail_build();
				return;
			}
			
			std::string command = "ar ";

			if(this->archive_insert_files) command += "r";
			if(this->archive_create_if_not_exists) command += "c";
			if(this->archive_index) command += "s";

			command += " " + output->get_file_name();
			
			for(fs::path path : this->build_files) {
				command += " " + path.string();
			}

			for(fs::path path : *source) {
				if(path.extension().string() != ".o") continue;
				command += " " + path.string();
			}

			if(!this->run_command(command)) {
				this->fail_build();
				return;
			}

			this->post_build();
			return;
		}

		if(output->type == DYNAMIC_LIB) {
			this->position_independant = true;
			if(!this->build_unlinked(source, output)) {
				this->fail_build();
				return;
			}

			std::string command = "gcc -shared -o " + output->get_file_name();

			for(fs::path path : this->build_files) {
				command += " " + path.string();
			}

			for(fs::path path : *source) {
				if(path.extension().string() != ".o") continue;
				command += " " + path.string();
			}

			for(fs::path path : this->compile_against_libs) {
				command += " " + path.string();
			}

			if(!this->run_command(command)) {
				this->fail_build();
				return;
			}

			this->post_build();
		}


	}

	inline void optimized_settings() override {
		this->optimization_level = 3;
		this->debug_info = false;
		this->archive_index = true;
	}

	inline bool build_outputless(FileSource* source) {
		return this->run_command(this->prepare_build_command(source));
	}

	inline bool build_singular(FileSource* source, fs::path out) {
		std::string command = this->prepare_build_command(source);

		command += " -o " + out.string();
		
		return this->run_command(command);
	}

	inline bool build_normal(FileSource* source, CompilerOutput* output) {
		std::string command = this->prepare_build_command(source);

		command += " -o " + output->get_file_name();

		return this->run_command(command);
	}


};

}