#pragma once
#include <string>
#include "Analyzer.h"

class AnalyzerResult :public Analyzer
{
public:
	AnalyzerResult();

	string combination(int coef);
};