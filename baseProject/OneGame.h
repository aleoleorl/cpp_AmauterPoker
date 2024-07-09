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
	int round; //������� �����

	Deck roundDeck; //������ ����
	vector <deck> table;

	AnalyzerResult an; //���������� �����

	int currentFirstPlayer; //������� ������������� ����� (�������� ��� �� �������� ������ ��������� � ����� ������)

	int curMaxBet; //������� ������
	int roundStartBet; //�������� ������ �� ������ ������
	int bank; //����

	void letsSitDownAtTheTable(Player *company[], int pl, rules gameRules, int currFirstPlayer); //���������� ����
	
	void allTakeACard(Player *company[], int pl, rules gameRules, int numOfThisTypeCard, int typeOfCard);
	
	void takeACard(Player *one, int pl, rules gameRules, int numOfThisTypeCard, int typeOfCard);

	void prepareMove(Player *company[], int pl, rules gameRules); //���������� ������
	
	void players(Player *company[], int pl, rules gameRules, int turns, int turn); //���� �������
	
	void transition(Player *company[], int pl, rules gameRules);

	int resultOfTheGame(Player *company[], int pl, rules gameRules, int turn, int turns, string name);

public:
	OneGame();

	const int Go(Player *company[], int pl, rules gameRules, int turns, int turn, int currFirstPlayer, string name); //�������� ����� ����
};
