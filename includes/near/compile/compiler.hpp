#include <near/file.hpp>
#include <near/compile/target.hpp>

#include <type_traits>
#include <bitset>

namespace near {

template <typename T, T last_one> class NearCompiler {
	static_assert(std::is_enum_v<T>, "T must be enum!");

private:
	std::bitset<last_one> options;

	bool run_compiler(FileStream stream, CompilerTarget target) {}

public:
	virtual bool compile(FileStream stream, CompilerTarget target) {}
	virtual bool compileToObject(FileStream stream, MultiFileCompilerTarget target) {}

	bool is_option_enabled(T option);
	void enable_option(T option);
	void disable_option(T option);

};

}