#include "pch.h"
#include "RailFence.h"

std::string kadenLib::RailFence::showFence(std::string plaintext, int height)
{
    std::string cipherText = "";
    char** fence = new char* [plaintext.length()];
    for (int i = 0; i < plaintext.length(); i++)
    {
        fence[i] = new char[height];
    }

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < plaintext.length(); i++)
        {
            fence[i][j] = '.';
        }
    }

    bool down = true;
    int j = 0;
    for (int i = 0; i < plaintext.length(); i++)
    {
        if (j < height && j >= 0) fence[i][j] = plaintext[i];
        if (down)
        {
            j++;
            if (j > height-1)
            {
                j-=2;
                down = !down;
            }
        }
        else
        {
            j--;
            if (j < 0)
            {
                j = 1;
                down = !down;
            }
        }
    }

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < plaintext.length(); i++)
        {
            cipherText.push_back(fence[i][j]);
        }
        cipherText.push_back('\n');
    }

    for (int i = 0; i < plaintext.length(); i++)
    {
        delete(fence[i]);
    }
    delete(fence);

    return cipherText;
}

std::string kadenLib::RailFence::encode(std::string plaintext, int height)
{
    std::string cipherText = "";
    char** fence = new char* [plaintext.length()];
    for (int i = 0; i < plaintext.length(); i++)
    {
        fence[i] = new char[height];
    }
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < plaintext.length(); i++)
        {
            fence[i][j] = '.';
        }
    }

    bool down = true;
    int j = 0;
    for (int i = 0; i < plaintext.length(); i++)
    {
        if (j < height && j >= 0) fence[i][j] = plaintext[i];
        if (down)
        {
            j++;
            if (j > height-1)
            {
                j-=2;
                down = !down;
            }
        }
        else
        {
            j--;
            if (j < 0)
            {
                j = 1;
                down = !down;
            }
        }
    }

    
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < plaintext.length(); i++)
        {
            if(fence[i][j] != '.') cipherText.push_back(fence[i][j]);
        }
    }

    for (int i = 0; i < plaintext.length(); i++)
    {
        delete(fence[i]);
    }
    delete(fence);

    return cipherText;
}
