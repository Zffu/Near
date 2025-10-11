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
		if(argc < 1) {
			std::cerr << "Usage: exec <profile>";
		}

		Near::current_profile = argv[0];

		if(Near::profiles.find(Near::current_profile) != Near::profiles.end()) {
			Near::profiles.at(Near::current_profile)();
		} else {
			std::cerr << "Error: The given profile doesn't exist! Here are the available profiles:\n";

			for(const auto& [key, val] : Near::profiles) {
				std::cerr << "- " << key << "\n";
			}
		}
	}
};

std::string Near::current_profile = "";

}