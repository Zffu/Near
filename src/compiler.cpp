#include <near/compile/compiler.hpp>

using namespace near;


template <typename F, typename O, F last_flag, O last_option>
bool NearCompiler<F, O, last_flag, last_option>::is_flag_enabled(F option) {
	return this->options[option];
}

template <typename F, typename O, F last_flag, O last_option>
void NearCompiler<F, O, last_flag, last_option>::enable_flag(F option) {
	this->options[option] = true;
}


template <typename F, typename O, F last_flag, O last_option>
void NearCompiler<F, O, last_flag, last_option>::disable_flag(F option) {
	this->options[option] = false;
}

template <typename F, typename O, F last_flag, O last_option>
template <typename V> V NearCompiler<F, O, last_flag, last_option>::get_option(O option, V def) {
	if(this->options[option] <= 0) return def;
	return (V) (this->options[option] - 1);
}

template <typename F, typename O, F last_flag, O last_option>
template <typename V> void NearCompiler<F, O, last_flag, last_option>::set_option(O option, V val) {
	this->options[option] = val + 1;
}

template <typename F, typename O, F last_flag, O last_option>
bool NearCompiler<F, O, last_flag, last_option>::has_option(O option) {
	return this->options[option] > 0;
} 

template <typename F, typename O, F last_flag, O last_option>
std::string NearCompiler<F, O, last_flag, last_option>::get_flag_cmd(F flag) {
	if(this->is_flag_enabled(flag)) return "";
	
	std::string(" ");

	
}