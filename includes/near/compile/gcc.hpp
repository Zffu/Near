#include <near/compile/compiler.hpp>

using namespace near;

namespace near::gcc {

enum GCCSTDs {
	C17,
	C18,

	CPP_17,
	CPP_20
};


enum FVisibility {
	DEFAULT,
	INTERNAL,
	HIDDEN,
	PROTECTED
};

enum GCCCompilerOptions {
	STD, FVISIBILITY
};

enum GCCCompilerFlags {
	LINK_ONLY,
	NO_ASSEMBLE,
	PREPROCESS_ONLY,

	ANSI,
	GNU89_INLINE,

	NO_ASM,

	NO_BUILTIN,

	FREE_STANDING,

	STATIC_LIBGCC,
	STATIC_LIBGPP,

	SHARED,

	NO_DEBUG,
	DEBUG
};

class GCCCompiler: public NearCompiler<GCCCompilerFlags, GCCCompilerOptions, DEBUG, FVISIBILITY> {
public:
	std::string get_flag_cmd(GCCCompilerFlags flag) override;
	std::string get_option_cmd(GCCCompilerOptions option) override;
};

}