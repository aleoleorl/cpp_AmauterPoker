#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include "Structures.h"

class PlayerTable :public Player
{
	//void showCard(deck card)

public:
	PlayerTable();

	/*int turn(rules gameRules)
	{
		//Hey! Are you crazy? What do you want from table?!
		return 0;
	}*/

	void getCharas(int mn, string nm);

	//void clearHand() //������ ����
	//void getOneCard(deck card) //����� ���� �����	

	void showCards(int iAm, int currIs, int curPlayer, int nothingGood);
};
