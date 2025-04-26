#pragma once
#include <string>
namespace kadenLib
{
	struct BinMorse_s
	{
		unsigned long long* message;
		unsigned numOfSections;
	};



	class Morse
	{
	private:
		std::string morseLetters[26] = {
			".-",
			"-...",
			"-.-.",
			"-..",
			".",
			"..-.",
			"--.",
			"....",
			"..",
			".---",
			"-.-",
			".-..",
			"--",
			"-.",
			"---",
			".--.",
			"--.-",
			".-.",
			"...",
			"-",
			"..-",
			"...-",
			".--",
			"-..-",
			"-.--",
			"--.."
		};
		std::string morseNumbers[10] = {
			"-----",
			".----",
			"..---",
			"...--",
			"....-",
			".....",
			"-....",
			"--...",
			"---..",
			"----."
		};


	public:
		std::string morseTable();
		std::string encode(std::string plainText);
		std::string encodeBin(std::string plainText);
		std::string encodeX(std::string plainText);
	};
}