#pragma once
#include <string>
#include <iostream>
namespace kadenLib
{
	class RailFence
	{
	public:
		std::string showFence(std::string plaintext, int height);
		std::string encode(std::string plaintext, int height);
	};
}