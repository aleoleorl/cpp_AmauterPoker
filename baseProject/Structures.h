#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct deck
{
	int number;
	int suit;
	int viewIt=-1; //����� 2 - ������� ��� ����, 1 - ������ ��� ������,
                    // 0 - ������� ��� ����, -1 - �� ����� ��������
};

struct game //���������� ����� � ����������� ����
{
	string name;//�������� ����
	int games;//������� ���
	int wins;//�� ��� ��������
	/*
	[name
	]gamename
	=games
	+wins
	]gamename
	=games
	+wins
	*/
};

struct player
{
	string name;
	int money;
};

struct oneTurn
{
	int cardsToPlayerOpen; //1
	int cardsToPlayerOpenForMe; //2
	int cardsToPlayerClose; //3
	int cardsOnTableOpen; //4
	int cardsOnTableClose; //5
	int cardsCanChangeOnHande; //6
};
struct rules
{
	string name; //n
	string rule; //r
	int maxPlayers; //1
	int tours; //������� //2
	vector <oneTurn> turns; //����� � ������ //t
	int chooseCardChanging; //����� �� ������ ����� � ���� //3
	int bet; //������� ������ //4
	int maxBet; //������������ ������ //5
	int firstPlayerChanging; //�������� �� ��������� //6
	int startBet; // ��� ��������� ������ ���� 0 - ����������� 1 - ������ �����, 2 - (������ ������ ����������, ������ ������), 3 - (������ ������ ����������, ������ - ������),
										//9 - ��� //7
	int fromHand; //���� ���������� �� ����� 0, ����������, ������� ���� ����� ������ ������� �� ���� ��� ���� ����������
					//��������� ����� ���������� �� ����� //8
};

class Structures
{
};
