#include "pch.h"
#include "EnglishLetterFrequency.h"

namespace kadenLib
{
	EnglishLetterFrequency::EnglishLetterFrequency()
	{
		ELFarray[0] = 0.082;
		ELFarray[1] = 0.015;
		ELFarray[2] = 0.028;
		ELFarray[3] = 0.043;
		ELFarray[4] = 0.13;
		ELFarray[5] = 0.022;
		ELFarray[6] = 0.02;
		ELFarray[7] = 0.061;
		ELFarray[8] = 0.07;
		ELFarray[9] = 0.0015;
		ELFarray[10] = 0.0077;
		ELFarray[11] = 0.04;
		ELFarray[12] = 0.025;
		ELFarray[13] = 0.067;
		ELFarray[14] = 0.075;
		ELFarray[15] = 0.019;
		ELFarray[16] = 0.00095;
		ELFarray[17] = 0.06;
		ELFarray[18] = 0.063;
		ELFarray[19] = 0.091;
		ELFarray[20] = 0.028;
		ELFarray[21] = 0.0098;
		ELFarray[22] = 0.024;
		ELFarray[23] = 0.0015;
		ELFarray[24] = 0.02;
		ELFarray[25] = 0.00074;
	}

	EnglishLetterFrequency EnglishLetterFrequency::get()
	{
		return *this;
	}

	void EnglishLetterFrequency::countLetters(std::string s)
	{
		std::string rawText = "";
		for (int i = 0; i < s.length(); i++)
		{
			s[i] = toupper(s[i]);
			if (s[i] >= 65 && s[i] <= 90) rawText.push_back(s[i]);
		}

		totalLetters = rawText.length();

		for (int i = 0; i < 26; i++)
		{
			ELFarray[i] = 0.0;
		}

		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < rawText.length(); j++)
			{
				if (rawText[j] == (char)(i + 65))
				{
					ELFarray[i] += 1.0;
				}
			}
		}
	}

	void EnglishLetterFrequency::set(EnglishLetterFrequency x)
	{
		for (int i = 0; i < 26; i++)
		{
			ELFarray[i] = x.ELFarray[i];
		}
	}

	void EnglishLetterFrequency::scale(double x)
	{
		for (int i = 0; i < 26; i++)
		{
			ELFarray[i] *= x;
		}
	}

	void EnglishLetterFrequency::add(double x)
	{
		for (int i = 0; i < 26; i++)
		{
			ELFarray[i] += x;
		}
	}

	void EnglishLetterFrequency::add(EnglishLetterFrequency x)
	{
		for (int i = 0; i < 26; i++)
		{
			ELFarray[i] += x.ELFarray[i];
		}
	}

	void EnglishLetterFrequency::mult(EnglishLetterFrequency x)
	{
		for (int i = 0; i < 26; i++)
		{
			ELFarray[i] *= x.ELFarray[i];
		}
	}

	void EnglishLetterFrequency::divide(EnglishLetterFrequency x)
	{
		for (int i = 0; i < 26; i++)
		{
			ELFarray[i] /= x.ELFarray[i];
		}
	}

	void EnglishLetterFrequency::shift()
	{
		double buf = ELFarray[0];
		for (int i = 0; i < 25; i++)
		{
			ELFarray[i] = ELFarray[i + 1];
		}
		ELFarray[25] = buf;
	}

	double EnglishLetterFrequency::indexOfCoincidence(std::string s)
	{
		double ioc = 0.0;
		int totalCount = 0;
		int letterCount = 0;

		for (int i = 0; i < s.length(); i++)
		{
			s[i] = toupper(s[i]);
			if (s[i] >= 65 && s[i] <= 90) totalCount++;
		}


		for (char i = 65; i <= 90; i++)
		{
			for (int j = 0; j < s.length(); j++)
			{
				if (s[j] == i) letterCount++;
			}

			ioc += ((double)letterCount * ((double)letterCount - 1)) / ((double)totalCount * ((double)totalCount - 1));
			letterCount = 0;
		}


		return ioc;
	}

	double EnglishLetterFrequency::chiTest(EnglishLetterFrequency x)
	{
		double chiScore = 0;
		EnglishLetterFrequency buf;
		buf.set(*this);
		x.scale(-1.0);
		buf.add(x);
		buf.mult(buf);
		x.scale(-1.0);
		buf.divide(x);

		for (int i = 0; i < 26; i++)
		{
			chiScore += buf.ELFarray[i];
		}



		return chiScore;
	}

	double EnglishLetterFrequency::chiTestGT()
	{
		EnglishLetterFrequency gt;
		double chiScore = 0;
		EnglishLetterFrequency buf;
		buf.set(*this);
		buf.scale(1.0 / totalLetters);
		gt.scale(-1.0);
		buf.add(gt);
		buf.mult(buf);
		gt.scale(-1.0);
		buf.divide(gt);

		for (int i = 0; i < 26; i++)
		{
			chiScore += buf.ELFarray[i];
		}

		return chiScore;
	}

	std::string EnglishLetterFrequency::toString()
	{
		std::string retString = "";

		for (int i = 0; i < 26; i++)
		{
			retString.push_back((char)(i + 65));
			retString.append(":\t");
			retString.append(std::to_string(ELFarray[i]));
			retString.push_back('\n');
		}

		return retString;
	}


}