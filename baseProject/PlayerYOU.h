#pragma once
#include <string>
#include <vector>
#include <conio.h>
#include "PlayerInGame.h"
#include "Structures.h"

class PlayerYOU :public PlayerInGame
{
public:
	PlayerYOU();

	int turn(Player *company[], int pl, rules gameRules, int round, int &curMaxBet, int currentFirstPlayer, int roundStartBet, int &bank, int myI);

	void turnB();

	void showCards(int iAm, int currIs, int curPlayer, int lenName);

	vector <deck> getPrioritet(vector <deck> table, rules gameRules);
};
