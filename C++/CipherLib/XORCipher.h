#pragma once
#include <string>
#include <stdio.h>
#include <time.h>
namespace kadenLib
{
	class XORCipher
	{
	public:
		XORCipher();
		std::string key;
		void genKey();
		std::string encode(std::string plaintext);
		std::string xorStrings(std::string s1, std::string s2);
	};
}