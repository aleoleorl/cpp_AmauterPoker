#pragma once
#include <vector>
#include <iostream>
#include "Structures.h"

using namespace std;

class Deck
{
private:

	vector <deck> defaultDeck; //������, ������������ ��� ����
	vector <deck> gameDeck;
	
	void showDeck(vector <deck> curDeck);

public:

	Deck();

	vector <deck> Stir(); //������������ �����

	deck getOneCard();
};
