#include <near/near.hpp>
#include <near/compiler.hpp>
#include <near/files.hpp>
#include <near/gcc.hpp>

using namespace near;
using namespace near::compilers;

void normal_profile() {
	GCCCompiler compiler("c++20");

	compiler.add_include_path("near");
	
	near::FolderFileSource source("bob");
	source.add_ext(".c");
	source.add_ext(".cpp");

	compiler.debug_settings();
	compiler.build(&source, "bobby.exe");
}

int main(int argc, char** argv) {
	Near::register_profile("normal", normal_profile);
	
	Near::init(argc, argv);
	return 1;
}