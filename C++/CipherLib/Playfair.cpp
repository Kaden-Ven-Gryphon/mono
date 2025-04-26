#include "pch.h"
#include "Playfair.h"

std::string kadenLib::Playfair::genFull66Key(std::string partialKey)
{
    std::string fullKey = "";
    std::string alpha = "";
    for (int i = 0; i < 26; i++)
    {
        alpha.push_back((char)(i + 65));
    }
    for (int i = 0; i < 10; i++)
    {
        alpha.push_back((char)(i + 48));
    }

    for (int i = 0; i < partialKey.length(); i++)
    {
        for (int j = 0; j < alpha.length(); j++)
        {
            if (alpha[j] == partialKey[i])
            {
                fullKey.push_back(alpha[j]);
                alpha.erase(j, 1);
                break;
            }
        }
    }
    for (int i = 0; i < alpha.length(); i++)
    {
        fullKey.push_back(alpha[i]);
    }



    return fullKey;
}

std::string kadenLib::Playfair::genFull65Key(std::string partialKey)
{
    std::string fullKey = "";
    std::string alpha = "";
    for (int i = 0; i < 26; i++)
    {
        alpha.push_back((char)(i + 65));
    }
    alpha.push_back(' ');
    alpha.push_back(',');
    alpha.push_back('.');
    alpha.push_back('?');

    for (int i = 0; i < partialKey.length(); i++)
    {
        for (int j = 0; j < alpha.length(); j++)
        {
            if (alpha[j] == partialKey[i])
            {
                fullKey.push_back(alpha[j]);
                alpha.erase(j, 1);
                break;
            }
        }
    }
    for (int i = 0; i < alpha.length(); i++)
    {
        fullKey.push_back(alpha[i]);
    }



    return fullKey;
}

std::string kadenLib::Playfair::encode65(std::string plainText, std::string fullKey, int direction)
{
    std::string cipherText = "";

    if (plainText.length() % 2 != 0) plainText.push_back('X');

    for (int i = 0; i < plainText.length(); i++)
    {
        plainText[i] = toupper(plainText[i]);
        if (plainText[i] <= 90 && plainText[i] >= 65) continue;
        if (plainText[i] == ' ') continue;
        if (plainText[i] == ',') continue;
        if (plainText[i] == '.') continue;
        if (plainText[i] == '?') continue;
        plainText.erase(i, 1);
        i--;
    }


    for (int i = 0; i < plainText.length(); i += 2)
    {
        int index1x = 0;
        int index1y = 0;
        int index2x = 0;
        int index2y = 0;

        for (int j = 0; j < 30; j++)
        {
            if (plainText[i] == fullKey[j])
            {
                index1y = j;
            }
        }
        index1x = index1y % 5;
        index1y /= (int)5;

        for (int j = 0; j < 30; j++)
        {
            if (plainText[i+1] == fullKey[j])
            {
                index2y = j;
            }
        }
        index2x = index2y % 5;
        index2y /= (int)5;

        if (index1x == index2x || index1y == index2y)
        {
            switch (direction)
            {
            case 3:
                index1y++;
                if (index1y > 5) index1y = 0;
                index2y++;
                if (index2y > 5) index2y = 0;
                break;
            case 2:
                index1x++;
                if (index1x > 4) index1x = 0;
                index2x++;
                if (index2x > 4) index2x = 0;
                break;
            case 1:
                index1y--;
                if (index1y < 0) index1y = 5;
                index2y--;
                if (index2y < 0) index2y = 5;
                break;
            case 4:
            default:
                index1x--;
                if (index1x < 0) index1x = 4;
                index2x--;
                if (index2x < 0) index2x = 4;
                break;
            }

            cipherText.push_back(fullKey[(index1y * 5 + index1x)]);
            cipherText.push_back(fullKey[(index2y * 5 + index2x)]);
        }
        else
        {
            cipherText.push_back(fullKey[(index1y * 5 + index2x)]);
            cipherText.push_back(fullKey[(index2y * 5 + index1x)]);
        }
    }

    return cipherText;
}
