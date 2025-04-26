#include "pch.h"
#include "VigenereCipher.h"

namespace kadenLib
{
    VigenereCipher::VigenereCipher()
    {
        aOffset = 1;
        maxKeyLength = 100;
        iocError = 0.01f;
        targetIoc = 0.0667;
    }


    std::string VigenereCipher::visualizeKey(std::string key)
    {
        std::string alpha = "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";
        std::string ret = "";

        for (int i = 0; i < key.length(); i++)
        {
            key[i] = toupper(key[i]);
        }

        for (int i = 0; i < key.length(); i++)
        {
            int shift = (int)key[i] - 65 + aOffset;
            std::string shiftedAlpha = "";
            for (int j = 0; j < alpha.length(); j += 2)
            {
                char buf = alpha[j] + shift;
                if (buf > 90) buf -= 26;
                shiftedAlpha.push_back(buf);
                shiftedAlpha.push_back(' ');
            }
            shiftedAlpha.pop_back();
            std::cout << "___________________________________________________________\n";
            std::cout << std::setw(2) << shift << " " << key[i] << "\t" << alpha << std::endl;
            std::cout << "\t" << shiftedAlpha << std::endl;
            std::cout << "___________________________________________________________\n";

        }
        return "";
    }

    int VigenereCipher::iocKeyLengthTest(std::string encodedText)
    {
        std::string rawText = "";
        EnglishLetterFrequency elf;


        for (int i = 0; i < encodedText.length(); i++)
        {
            encodedText[i] = toupper(encodedText[i]);
            if (encodedText[i] >= 65 && encodedText[i] <= 90) rawText.push_back(encodedText[i]);
        }


        int retKeyLength = -1;

        for (int i = 1; i <= maxKeyLength; i++)
        {
            std::string nthLetters = "";

            for (int j = 0; j < rawText.length(); j += i)
            {
                nthLetters.push_back(rawText[j]);
            }

            float ioc = elf.indexOfCoincidence(nthLetters);
            if (ioc < targetIoc + iocError && ioc > targetIoc - iocError)
            {
                retKeyLength = i;
                break;
            }
        }



        return retKeyLength;
    }

    int VigenereCipher::findOffset(std::string encodedText)
    {

        double count = 0;
        std::string rawText = "";
        EnglishLetterFrequency elf;
        int offset = 0;
        double lowestChi = 999999999.0;

        for (int i = 0; i < encodedText.length(); i++)
        {
            encodedText[i] = toupper(encodedText[i]);
            if (encodedText[i] >= 65 && encodedText[i] <= 90) rawText.push_back(encodedText[i]);
        }

        elf.countLetters(rawText);

        count = rawText.length();

        lowestChi = elf.chiTestGT();

        for (int i = 1; i < 27; i++)
        {
            elf.shift();
            double buf = elf.chiTestGT();

            if (buf < lowestChi)
            {
                lowestChi = buf;
                offset = i;
            }
        }

        return offset + aOffset;
    }

    std::string VigenereCipher::breakKey(std::string encodedText)
    {
        std::string retKey = "";
        int keyLength = iocKeyLengthTest(encodedText);

        std::string rawText = "";
        for (int i = 0; i < encodedText.length(); i++)
        {
            encodedText[i] = toupper(encodedText[i]);
            if (encodedText[i] >= 65 && encodedText[i] <= 90) rawText.push_back(encodedText[i]);
        }


        for (int i = 0; i < keyLength; i++)
        {
            std::string nthLetters = "";
            for (int j = i; j < rawText.length(); j += keyLength)
            {
                nthLetters.push_back(rawText[j]);
            }
            retKey.push_back((char)(findOffset(nthLetters) + 65));
        }
        return retKey;
    }

    std::string VigenereCipher::encode(std::string plainText, std::string key)
    {
        for (int i = 0; i < plainText.length(); i++)
        {
            plainText[i] = toupper(plainText[i]);
        }
        for (int i = 0; i < key.length(); i++)
        {
            key[i] = toupper(key[i]);
        }


        std::string encodedText = "";
        int keyIndexMax = key.length() - 1;
        int keyIndex = 0;
        for (int i = 0; i < plainText.length(); i++)
        {
            if (plainText[i] == ' ')
            {
                encodedText.push_back(' ');
                continue;
            }
            else if (plainText[i] < 65 || plainText[i] > 90)
            {
                continue;
            }

            int shift = (int)key[keyIndex] - 65 + aOffset;
            char buf = plainText[i] + shift;
            if (buf > 90) buf -= 26;
            encodedText.push_back(buf);

            keyIndex++;
            if (keyIndex > keyIndexMax) keyIndex = 0;
        }

        return encodedText;
    }

    std::string VigenereCipher::decode(std::string encodedText, std::string key)
    {
        for (int i = 0; i < encodedText.length(); i++)
        {
            encodedText[i] = toupper(encodedText[i]);
        }
        for (int i = 0; i < key.length(); i++)
        {
            key[i] = toupper(key[i]);
        }


        std::string plainText = "";
        int keyIndexMax = key.length() - 1;
        int keyIndex = 0;

        for (int i = 0; i < encodedText.length(); i++)
        {
            if (encodedText[i] == ' ')
            {
                plainText.push_back(' ');
                continue;
            }
            else if (encodedText[i] < 65 || encodedText[i] > 90)
            {
                continue;
            }

            int shift = (int)key[keyIndex] - 65 + aOffset;
            char buf = encodedText[i] - shift;
            if (buf < 65) buf += 26;
            plainText.push_back(buf);

            keyIndex++;
            if (keyIndex > keyIndexMax) keyIndex = 0;
        }

        return plainText;
    }

    VkeyList VigenereCipher::generateKeys(int length)
    {
        //MAX LENGTH FOR THIS IS 5
        VkeyList retList;

        retList.length = (int)pow((double)26, (double)length);

        retList.keys = new std::string[retList.length];

        for (int i = 0; i < retList.length; i++)
        {
            retList.keys[i] = "";
            for (int j = 0; j < length; j++)
            {
                retList.keys[i].push_back((char)((int)floor(i / pow((double)26, (double)j)) % 26 + 65));
            }
        }

        return retList;
    }

    void VigenereCipher::genKeysFile(std::string fileName, int length)
    {
        std::ofstream fp;
        fp.open(fileName);

        unsigned long long int number = (unsigned long long int)pow((double)26, (double)length);

        fp << number << std::endl;


        for (unsigned long long int i = 0; i < number; i++)
        {
            std::string buf = "";
            for (int j = 0; j < length; j++)
            {
                buf.push_back((char)((unsigned long long int)floor((double)i / pow((double)26, (double)j)) % 26 + 65));
            }
            fp << buf << std::endl;
        }

        return;

        fp.close();
    }



}