#include "pch.h"
#include "Hitomezashi.h"


namespace kadenLib
{
	std::string Hitomezashi::stitch64Patch(unsigned long long seedTop, unsigned long long seedSide)
	{
		std::string retStitch = "";
		unsigned long long iBit = (unsigned long long)1;
		unsigned long long jBit = (unsigned long long)1;

		for (int i = 0; i < 64; i++)
		{
			if ((seedSide & iBit) == iBit)
			{
				for (int j = 0; j < 32; j++)
				{
					if ((seedTop & jBit) == jBit) { retStitch.append("_|"); }
					else { retStitch.append("_ "); }
					jBit <<= 1;
					if ((seedTop & jBit) == jBit) { retStitch.append(" |"); }
					else { retStitch.append("  "); }
					jBit <<= 1;
				}
				retStitch.push_back('\n');
			}
			else
			{
				for (int j = 0; j < 32; j++)
				{
					if ((seedTop & jBit) == jBit) retStitch.append(" |");
					else retStitch.append("  ");
					jBit <<= 1;
					if ((seedTop & jBit) == jBit) retStitch.append("_|");
					else retStitch.append("_ ");
					jBit <<= 1;
				}
				retStitch.push_back('\n');
			}
			iBit <<= 1;
			jBit = (unsigned long long)1;
			seedTop = ~seedTop;
		}


		return retStitch;
	}
	std::string Hitomezashi::fill(std::string hs, char c)
	{
		std::string retFill = "";
		int i = 0;
		bool swap = false;
		bool fill = false;

		while (i <= hs.length() - 1)
		{
			if (hs[i] == '_') swap = !swap;
			while (i <= hs.length())
			{
				if (hs[i] == '\n')
				{
					retFill.push_back('\n');
					i++;
					break;
				}

				if (fill) retFill.push_back(c);
				else retFill.push_back(' ');
				i++;

				if (hs[i] == '\n')
				{
					retFill.push_back('\n');
					i++;
					break;
				}

				if (hs[i] == '|') fill = !fill;
				i++;
			}
			fill = swap;
		}
		return retFill;
	}
}



