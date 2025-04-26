#include "pch.h"
#include "XORCipher.h"

kadenLib::XORCipher::XORCipher()
{
	genKey();
}

void kadenLib::XORCipher::genKey()
{
	srand(time(0));
	key = "";
	for (int i = 0; i < 16; i++)
	{
		key.push_back((char)(rand() % 256));
	}
}

std::string kadenLib::XORCipher::encode(std::string plaintext)
{
	std::string ciphertext = "";

	for (int i = 16-(plaintext.length() % 16); i > 0; i--)
	{
		if (i == 16) break;
		plaintext.push_back(' ');
	}


	for (int i = 0; i < plaintext.length(); i++)
	{
		ciphertext.push_back(plaintext[i] ^ key[i % 16]);
	}

	return ciphertext;
}

std::string kadenLib::XORCipher::xorStrings(std::string s1, std::string s2)
{
	int length = s1.length();
	if (s2.length() < length) length = s2.length();

	for (int i = 0; i < length; i++)
	{
		s1[i] = s1[i] ^ s2[i];
	}
	return s1;
}
