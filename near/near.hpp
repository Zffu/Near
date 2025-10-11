#pragma once

#include <string>
#include <iostream>
#include <functional>

namespace near {

class Near {
private:
	static std::unordered_map<std::string, std::function<void()>> profiles;

public:
	static std::string current_profile;

	static void register_profile(std::string profile_name, std::function<void()> exec) {
		Near::profiles.emplace(profile_name, exec);
	}

	static void init(int argc, char** argv) {
		if(argc < 2) {
			std::cout << "Usage: exec <profile>";
			return;
		}

		Near::current_profile = argv[1];

		if(Near::profiles.contains(Near::current_profile)) {
			Near::profiles.at(Near::current_profile)();
		} else {
			std::cout << "Error: The profile " << Near::current_profile << " doesn't exist! Here are the available profiles:\n";

			for(const auto& [key, val] : Near::profiles) {
				std::cerr << "- " << key << "\n";
			}
		}
	}
};

std::string Near::current_profile = "";
std::unordered_map<std::string, std::function<void()>> Near::profiles = {}; 

}