#include "PlayerInGame.h"

PlayerInGame::PlayerInGame()
{
	chara.money = 0;
	chara.name = "noname";

	myBet = 0;

	inGame = 0;
}

void PlayerInGame::getCharas(int mn, string nm)
{
	chara.money = mn;
	chara.name = nm;
}

string PlayerInGame::setName()
{
	return chara.name;
}

vector <int> PlayerInGame::getCardToChange()
{
	vector <int> temp = toCange;
	toCange.erase(toCange.begin(), toCange.end());
	return temp;
}

void PlayerInGame::getMoney(int n)
{
	chara.money += n;
}

int PlayerInGame::setMoney()
{
	return chara.money;
}

void PlayerInGame::clearBet()
{
	myBet = 0;
}

int PlayerInGame::makeBet(int b)
{
	int forRet = 0;
	if (chara.money >= b)
	{
		chara.money -= b;
		myBet += b;
		forRet = b;
	}
	if (chara.money < b)
	{
		myBet += chara.money;
		forRet = chara.money;
		chara.money = 0;
		inGame = -1;
	}
	return forRet;
}