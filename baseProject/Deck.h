#pragma once
#include <vector>
#include <iostream>
#include "Structures.h"

using namespace std;

class Deck
{
private:

	vector <deck> defaultDeck; //колода, используемая для игры
	vector <deck> gameDeck;
	
	void showDeck(vector <deck> curDeck);

public:

	Deck();

	vector <deck> Stir(); //перемешиваем карты

	deck getOneCard();
};
