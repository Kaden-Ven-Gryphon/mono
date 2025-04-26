#pragma once
#include<string>
namespace kadenLib
{
	unsigned long long stringToULL(std::string s)
	{
		unsigned long long ret = 0;
		unsigned long long bit = 1;

		for (int i = 0; i < 64; i++)
		{
			if (i < s.length())
			{
				if (s[i] == '1')
				{
					ret += bit;
				}
			}
			bit <<= 1;
		}
		return ret;
	}
}