#pragma once
#include <string>
#include <vector>
#include <conio.h>
#include "PlayerInGame.h"
#include "Structures.h"
#include "Analyzer.h"
#include "AnalyzerSmart.h"

using namespace std;

class PlayerCPU :public PlayerInGame
{	
	AnalyzerSmart an;
	
public:
	PlayerCPU();

	int turn(Player *company[], int pl, rules gameRules, int round, int &curMaxBet, int currentFirstPlayer, int roundStartBet, int &bank, int myI); //ход компа
	
	void turnB();
		
	void showCards(int iAm, int currIs, int curPlayer, int lenName);

	vector <deck> getPrioritet(vector <deck> table, rules gameRules);
};
