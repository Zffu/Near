#include <string>
#include <vector>

#include <near/file.hpp>
#include <near/compile/build.hpp>

#include <functional>

#define ROUTINE_STEP_CALL(x) \
	x; \
	if(!NearBuildInstance::current->active) return; 

namespace near {

class Routine {
private:
	FileStream* source_stream;
	std::function<void(Routine* routine, NearBuildInstance* build)> callptr;

	Routine* prev;
	Routine* next;

	Routine* child;
	Routine* child_leaf;

public:
	Routine(std::function<void(Routine* routine, NearBuildInstance* build)> rountine_call) {
		this->source_stream = nullptr;
		this->callptr = rountine_call;
		this->prev = nullptr;
		this->next = nullptr;
		this->child = nullptr;
		this->child_leaf = nullptr;
	}

	Routine(std::function<void(Routine* routine, NearBuildInstance* build)> routine_call, FileStream* stream) {
		this->source_stream = stream;
		this->callptr = routine_call;
		this->prev = nullptr;
		this->next = nullptr;
		this->child = child;
		this->child_leaf = child_leaf;
	}

	void append_child(Routine* routine);
	void append_next(Routine* routine);

	void call();

};		

}