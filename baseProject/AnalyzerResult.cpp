#include "AnalyzerResult.h"

AnalyzerResult::AnalyzerResult()
{
}

string AnalyzerResult::combination(int coef)
{
	if (coef >= 10)
	{
		return "Royal Flush";
	}
	if (coef >= 9 && coef <10)
	{
		return "Straight Flush";
	}
	if (coef >= 8 && coef <9)
	{
		return "Four of a Kind";
	}
	if (coef >= 7 && coef <8)
	{
		return "Full House";
	}
	if (coef >= 6 && coef <7)
	{
		return "Flush";
	}
	if (coef >= 5 && coef <6)
	{
		return "Straight";
	}
	if (coef >= 4 && coef <5)
	{
		return "Three of a Kind";
	}
	if (coef >= 3 && coef <4)
	{
		return "Two-pair";
	}
	if (coef >= 2 && coef <3)
	{
		return "One-pair";
	}
	if (coef >= 1 && coef <2)
	{
		return "High-card";
	}
	return " ";
}