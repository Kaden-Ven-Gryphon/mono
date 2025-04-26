#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "EnglishLetterFrequency.h"

namespace kadenLib
{
	struct VkeyList
	{
		int length = 0;
		std::string* keys = nullptr;
	};


	class VigenereCipher
	{
	public:
		int aOffset;
		int maxKeyLength;
		float iocError;
		float targetIoc;

		VigenereCipher();




		std::string visualizeKey(std::string key);
		int iocKeyLengthTest(std::string encodedText);
		int findOffset(std::string encodedText);
		std::string breakKey(std::string encodedText);


		std::string encode(std::string plainText, std::string key);
		std::string decode(std::string encodedText, std::string key);


		VkeyList generateKeys(int length);
		void genKeysFile(std::string fileName, int length);


	};
}