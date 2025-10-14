#include <near/compile/compiler.hpp>

using namespace near;

template <typename T, T last_one> bool NearCompiler<T, last_one>::is_option_enabled(T option) {
	return this->options[option];
}

template <typename T, T last_one> void NearCompiler<T, last_one>::enable_option(T option) {
	this->options[option] = true;
}

template <typename T, T last_one> void NearCompiler<T, last_one>::disable_option(T option) {
	this->options[option] = false;
}


