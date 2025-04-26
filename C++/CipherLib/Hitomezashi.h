#pragma once
#include <string>
namespace kadenLib
{
	class Hitomezashi
	{
	public:
		std::string stitch64Patch(unsigned long long seedTop, unsigned long long seedSide);
		std::string fill(std::string hs, char c);
	};
}