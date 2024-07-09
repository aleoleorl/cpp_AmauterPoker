#pragma once
#include <string>
#include <conio.h>
#include "Structures.h"

using namespace std;

class RulesMaker
{
public:
	RulesMaker();

	rules ramRule();

	int loading(vector <rules> &pokers);

	void manager(vector <rules> &pokers);
};