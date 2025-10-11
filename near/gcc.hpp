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

	inline void build(FileSource* source, std::string out) {
		std::string command = "gcc -o " + out;

		if(this->compile_only) command += " -c";
		if(this->warnings) command += " -Wall";
		if(this->extra_warnings) command += " -Wextra";

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

		for(std::string path : *source) {
			command += " " + path;
		}

		std::cout << "Running: " << command;
		system(command.c_str());
	}


};

}