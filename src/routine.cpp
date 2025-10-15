#include <near/compile/routine.hpp>

using namespace near;

void Routine::call() {
	ROUTINE_STEP_CALL(this->callptr(this, NearBuildInstance::current))

	Routine* child = this->child;

	while(child != nullptr) {
		ROUTINE_STEP_CALL(child->call())
		child = child->next;
	}

	child = this->next;

	while(child != nullptr) {
		ROUTINE_STEP_CALL(child->call())
		child = child->next;
	}
}