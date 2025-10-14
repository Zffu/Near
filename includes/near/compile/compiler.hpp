#include <near/file.hpp>
#include <near/compile/target.hpp>

namespace near {

class NearCompiler {
private:
	bool run_compiler(FileStream stream, CompilerTarget target);

public:
	bool compile(FileStream stream, CompilerTarget target);
	bool compileToObject(FileStream stream, MultiFileCompilerTarget target);

};

}