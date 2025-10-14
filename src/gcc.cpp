#include <near/compile/gcc.hpp>

using namespace near::gcc;

std::string GCCCompiler::get_flag_cmd(GCCCompilerFlags flag) {
	if(!this->is_flag_enabled(flag)) return "";
	
	std::string ff(" ");

	char* flags[] = {"-c", "-S", "-e", "-fgnu-89-inline", "-fno-asm", "-ffreestanding", "-static-libgcc", "-static-libg++", "-shared", "-s", "-g"};
	ff += flags[flag];

	return ff;
}

std::string GCCCompiler::get_option_cmd(GCCCompilerOptions option) {
	if(!this->has_option(option)) return "";

	std::string o(" ");

	switch(option) {
		case GCCCompilerOptions::STD: 
			char* val[] = {"c17", "c18", "c++17", "c++20"};

			o += "std=";
			o += val[this->get_option<GCCSTDs>(option, C17)];
			return o;
		case GCCCompilerOptions::FVISIBILITY:
			char* val[] = {"default", "internal", "hidden", "protected"};

			o += "-fvisibility=";
			o += val[this->get_option<FVisibility>(option, DEFAULT)];
			return o;
	}

	return o;
}