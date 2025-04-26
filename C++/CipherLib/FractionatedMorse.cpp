#include "pch.h"
#include "FractionatedMorse.h"

namespace kadenLib
{
    FractionatedMorse::FractionatedMorse()
    {
        key = "";
        plainTextFileName = "FMtestText.txt";
    }
    std::string FractionatedMorse::finshKey(std::string partialKey)
    {
        std::string fullKey = "";
        char letters[26];
        for (int i = 0; i < 26; i++)
        {
            letters[i] = (char)(i + 65);
        }

        for (int i = 0; i < partialKey.length(); i++)
        {
            char buff = ' ';
            int index = -1;

            for (int j = i; j < 26; j++)
            {
                if (partialKey[i] == letters[j])
                {
                    index = j;
                    break;
                }
            }
            if (index >= 0)
            {
                buff = letters[index];
                for (int j = index; j > i; j--)
                {
                    letters[j] = letters[j - 1];
                }
                letters[i] = buff;
            }
        }

        for (int i = 0; i < 26; i++)
        {
            fullKey.push_back(letters[i]);
        }


        return fullKey;
    }
    std::string FractionatedMorse::encode(std::string plainText, std::string key)
    {
        Morse m;
        std::string morseX = m.encodeX(plainText);
        std::string cipherText = "";
        
        

        for (int i = 3-(morseX.length() % 3); i > 0; i--)
        {
            if (i == 3) break;
            morseX.push_back('x');
        }

        for (int i = 0; i < morseX.length(); i++)
        {
            switch (morseX[i])
            {
            case '.':
                morseX[i] = (char)0;
                break;
            case '-':
                morseX[i] = (char)1;
                break;
            case 'x':
                morseX[i] = (char)2;
                break;
            }
        }

        for (int i = 0; i < morseX.length(); i+=3)
        {
            int keyIndex = 0;
            keyIndex += 9 * ((int)morseX[i]);
            keyIndex += 3 * ((int)morseX[i + 1]);
            keyIndex += (int)morseX[i + 2];

            cipherText.push_back(key[keyIndex]);
        }


        return cipherText;
    }

}
