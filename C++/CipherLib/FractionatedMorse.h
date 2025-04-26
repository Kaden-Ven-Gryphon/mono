#pragma once
#include <string>
#include "Morse.h"
namespace kadenLib
{
	class FractionatedMorse
	{
	public:
		std::string key;
		std::string plainTextFileName;

		FractionatedMorse();

		std::string finshKey(std::string partialKey);
		std::string encode(std::string plainText, std::string key);

		std::string breakKey(std::string cipherText);

	private:
		
	};
}