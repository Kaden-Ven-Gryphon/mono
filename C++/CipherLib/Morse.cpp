#include "pch.h"
#include "Morse.h"


namespace kadenLib
{
    std::string kadenLib::Morse::morseTable()
    {
        std::string retTable = "";
        for (int i = 0; i < 26; i++)
        {
            retTable.push_back((char)(i + 65));
            retTable.append(":  ");
            retTable.append(morseLetters[i]);
            retTable.push_back('\n');
        }
        return retTable;
    }

    std::string kadenLib::Morse::encode(std::string plainText)
    {
        std::string retEncoded = "";
        std::string rawText = "";

        for (int i = 0; i < plainText.length(); i++)
        {
            plainText[i] = toupper(plainText[i]);
            if (plainText[i] == ' ') rawText.push_back(' ');
            else if ((plainText[i] >= 65 && plainText[i] <= 90) || (plainText[i] >= 48 && plainText[i] <= 57)) rawText.push_back(plainText[i]);
        }

        for (int i = 0; i < rawText.length(); i++)
        {
            if (rawText[i] == ' ')
            {
                retEncoded.append(" / ");
            }
            else if (rawText[i] < 65)
            {
                retEncoded.append(morseNumbers[(rawText[i] - 48)]);
                retEncoded.push_back(' ');
            }
            else
            {
                retEncoded.append(morseLetters[(rawText[i] - 65)]);
                retEncoded.push_back(' ');
            }
        }

        return retEncoded;
    }

    std::string kadenLib::Morse::encodeBin(std::string plainText)
    {
        std::string morseText = encode(plainText);
        std::string morseBin = "";
        unsigned numberOfBits = 0;

        for (int i = 0; i < morseText.length(); i++)
        {
            switch (morseText[i])
            {
            case '.':
                numberOfBits += 2; //1dit + 1ditSpace
                morseBin.append("10");
                break;
            case '-':
                numberOfBits += 4; //3dah + 1ditSpace
                morseBin.append("1110");
                break;
            case ' ':
                numberOfBits += 3; //3dahSpace
                morseBin.append("00");
                break;
            case '/':
                //numberOfBits += 1; //7 total 3 from space 1 from slash 3 from space
                //morseBin.append("0");
            default:
                break;
            }
        }





        return morseBin;
    }

    std::string Morse::encodeX(std::string plainText)
    {
        std::string morseText = encode(plainText);
        std::string morseX = "";
        for (int i = 0; i < morseText.length(); i++)
        {
            switch (morseText[i])
            {
            case '.':
                morseX.push_back('.');
                break;
            case '-':
                morseX.push_back('-');
                break;
            case ' ':
                morseX.append("x");
                break;
            case '/':
                morseX.append("xx");
                break;
            default:
                break;
            }
        }

        return morseX;
    }

}

