#include <near/compile/build.hpp>

#include <iostream>

using namespace near;

void NearBuildInstance::fail_build(std::string reason) {
	std::cout << "Build failed! Reason: " << reason;
	this->active = false;
}