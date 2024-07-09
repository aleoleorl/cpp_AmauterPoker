#include <vector>
#include <map>
#include <stdlib.h>
#include <conio.h>
#include "Player.h"
#include "Structures.h"
#include "Deck.h"
#include "AnalyzerResult.h"

class OneGame
{
private:
	int game;
	int round; //текущий раунд

	Deck roundDeck; //колода карт
	vector <deck> table;

	AnalyzerResult an; //анализатор побед

	int currentFirstPlayer; //текущий разыгрывающий игрок (меняется или не меняется каждое обращение к этому классу)

	int curMaxBet; //текущая ставка
	int roundStartBet; //величина ставки на начало раунда
	int bank; //банк

	void letsSitDownAtTheTable(Player *company[], int pl, rules gameRules, int currFirstPlayer); //подготовка игры
	
	void allTakeACard(Player *company[], int pl, rules gameRules, int numOfThisTypeCard, int typeOfCard);
	
	void takeACard(Player *one, int pl, rules gameRules, int numOfThisTypeCard, int typeOfCard);

	void prepareMove(Player *company[], int pl, rules gameRules); //подготовка раунда
	
	void players(Player *company[], int pl, rules gameRules, int turns, int turn); //ходы игроков
	
	void transition(Player *company[], int pl, rules gameRules);

	int resultOfTheGame(Player *company[], int pl, rules gameRules, int turn, int turns, string name);

public:
	OneGame();

	const int Go(Player *company[], int pl, rules gameRules, int turns, int turn, int currFirstPlayer, string name); //основной класс игры
};
