#pragma once
#include <conio.h>
#include "Player.h"
#include "Analyzer.h"

class AnalyzerSmart :public Analyzer
{
	double risker;

	int sum(int money, int curMaxBet, int myBet); //проверяем, хватает ли денег на ставку

	int mult(int money, int curMaxBet, int myBet, int roundStartBet, rules gameRules, int res); //проверяем, хватает ли денег на ставку

	double cardsRate(vector <double> coeff, int pl, int myI);

	double potentialRate(rules gameRules, int round);
	
public:
	AnalyzerSmart();

	int decision(Player *company[], int pl, rules gameRules, int round, int curMaxBet, int roundStartBet, int myBet, int myI);

	vector <int> toChange(vector <deck> onHand);
};

/*res == 1 " fold" << endl;
res == 2 " call" << endl;
res == 3 " check" << endl;
res == 4 " bet" << endl;
res == 5 " all-in" << endl;
res == 6 " raise" << endl;
*/