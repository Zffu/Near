#include <near.hpp>
#include <compiler.hpp>
#include <files.hpp>
#include <clang.hpp>

using namespace near;
using namespace near::compilers;

void build_normal() {
	ClangCompiler compiler("c++20");
	
	compiler.optimized_settings();

	FolderFileSource source = FolderFileSource("src");
	source.add_ext(".cpp");
	source.add_ext(".c");

	CompilerOutput output("out", EXECUTABLE);
	compiler.build(&source, &output);
}

int main(int argc, char** argv) {
	Near::register_profile("build", build_normal);
	Near::init(argc, argv);
}