#pragma once
#include <string>
#include <vector>
#include "Structures.h"
#include "Player.h"

class PlayerInGame : public Player
{
protected:
	player chara; //параметры игрока
	int myBet;
	vector <int> toCange; //вектор карт на смену

	//void showCard(deck card)

private:

public:
	PlayerInGame();

	void getCharas(int mn, string nm);

	string setName();

	vector <int> getCardToChange();

	void getMoney(int n);

	int setMoney();
		
	//void clearHand() //чистим руку
	//void getOneCard(deck card) //взять одну карту	

	void clearBet();

	int makeBet(int b);
};