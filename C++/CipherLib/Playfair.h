#pragma once
#include <string>
namespace kadenLib
{
	class Playfair
	{
	public:
		std::string genFull66Key(std::string partialKey);
		std::string genFull65Key(std::string partialKey);
		std::string encode65(std::string plainText, std::string fullKey, int direction);
	};
}