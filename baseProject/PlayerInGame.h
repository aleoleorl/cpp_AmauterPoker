#pragma once
#include <string>
#include <vector>
#include "Structures.h"
#include "Player.h"

class PlayerInGame : public Player
{
protected:
	player chara; //��������� ������
	int myBet;
	vector <int> toCange; //������ ���� �� �����

	//void showCard(deck card)

private:

public:
	PlayerInGame();

	void getCharas(int mn, string nm);

	string setName();

	vector <int> getCardToChange();

	void getMoney(int n);

	int setMoney();
		
	//void clearHand() //������ ����
	//void getOneCard(deck card) //����� ���� �����	

	void clearBet();

	int makeBet(int b);
};