#pragma once
#include <string>

namespace nu {
	inline std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		for (auto& c : lower) {
			c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
		}
		return lower;
	};
	inline std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		for (auto& c : upper) {
			c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		}
		return upper;
	};

	inline bool EqualsIgnoreCase(const std::string& str1, const std::string& str2) 
	{
		if(str1.size() != str2.size()) return false;
	
		return ToLower(str1) == ToLower(str2);
	}
}