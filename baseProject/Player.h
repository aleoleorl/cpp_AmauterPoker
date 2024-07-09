#pragma once
#include <string>
#include <vector>
#include "Structures.h"

class Player
{
protected:
	vector <deck> onHand; //����� �� �����
	
	void showCard(deck card);
		
public:
	int inGame; //1 - � ����, 0 - ���, -1 - ������ �� ���, -2 - ��� ����� ��� �������� ������

	Player();

	virtual int turn(Player *company[], int pl, rules gameRules, int round, int &curMaxBet, int currentFirstPlayer, int roundStartBet, int &bank, int myI); //������� ����

	virtual void turnB();

	virtual vector <int> getCardToChange(); //���������� ������ ����, ������� ���� ��������

	void changeCardInHand(deck card, int i); //������ ���������� ����� � ����

	virtual void getCharas(int mn, string nm);

	void clearHand(); //������ ����

	void getOneCard(deck card); //����� ���� �����

	vector <deck> showHand(); //�������� �����

	virtual vector <deck> getPrioritet(vector <deck> table, rules gameRules); //�������� ����������

	virtual void showCards(int iAm, int currIs, int curPlayer, int lenName);

	virtual void clearBet();

	virtual int makeBet(int b);

	virtual string setName();

	virtual int setMoney();

	virtual void getMoney(int n);

	void openCards(); //������ ��� ����� ���������
};
