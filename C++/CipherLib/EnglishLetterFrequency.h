#pragma once
#include <string>

namespace kadenLib
{
	class EnglishLetterFrequency
	{
	public:

		double ELFarray[26];
		double alpha = 0.05;
		double chiLowerBound = 15.3792;
		double chiUpperBound = 38.8851;
		double englishIOC = 0.06667;
		int totalLetters = 0;

		EnglishLetterFrequency();

		EnglishLetterFrequency get();

		void countLetters(std::string s);

		void set(EnglishLetterFrequency x);
		void scale(double x);
		void add(double x);
		void add(EnglishLetterFrequency x);
		void mult(EnglishLetterFrequency x);
		void divide(EnglishLetterFrequency x);
		void shift();

		double indexOfCoincidence(std::string s);

		double chiTest(EnglishLetterFrequency x);
		double chiTestGT();

		std::string toString();
	};
}