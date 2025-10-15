#include <near/file.hpp>
#include <near/compile/target.hpp>

#include <type_traits>
#include <bitset>
#include <unordered_map>

#include <string>

namespace near {

template <typename F, typename O, F last_flag, O last_option> class NearCompiler {
	static_assert(std::is_enum_v<F>, "F must be enum!");
	static_assert(std::is_enum_v<O>, "O must be enum!");


private:
	std::bitset<last_flag> flags;
	int options[last_option];

	virtual bool run_compiler(FileStream stream, CompilerTarget target) {}

public:
	virtual bool compile(FileStream stream, CompilerTarget target) {}
	virtual bool compileToObject(FileStream stream, MultiFileCompilerTarget target) {}

	/**
	 * Can be .o files or .dlls
	 */
	FileStream dependencies;

	bool is_flag_enabled(F option);
	void enable_flag(F option);
	void disable_flag(F option);

	template <typename V> V get_option(O option, V def);
	template <typename V> void set_option(O option, V val);
	bool has_option(O option);

	virtual std::string get_flag_cmd(F flag) {}
	virtual std::string get_option_cmd(O option) {}
};

}