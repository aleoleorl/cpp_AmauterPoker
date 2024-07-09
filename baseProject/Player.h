#pragma once
#include <string>
#include <vector>
#include "Structures.h"

class Player
{
protected:
	vector <deck> onHand; //карты на руках
	
	void showCard(deck card);
		
public:
	int inGame; //1 - в игре, 0 - пас, -1 - ставка на все, -2 - нет денег для текущего раунда

	Player();

	virtual int turn(Player *company[], int pl, rules gameRules, int round, int &curMaxBet, int currentFirstPlayer, int roundStartBet, int &bank, int myI); //функция хода

	virtual void turnB();

	virtual vector <int> getCardToChange(); //возвращаем номера карт, которые надо поменять

	void changeCardInHand(deck card, int i); //меняем конкретную карту в руке

	virtual void getCharas(int mn, string nm);

	void clearHand(); //чистим руку

	void getOneCard(deck card); //взять одну карту

	vector <deck> showHand(); //передать карты

	virtual vector <deck> getPrioritet(vector <deck> table, rules gameRules); //выбираем комбинацию

	virtual void showCards(int iAm, int currIs, int curPlayer, int lenName);

	virtual void clearBet();

	virtual int makeBet(int b);

	virtual string setName();

	virtual int setMoney();

	virtual void getMoney(int n);

	void openCards(); //делаем все карты открытыми
};
