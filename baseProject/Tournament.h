#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "OneGame.h"
#include "Player.h"
#include "PlayerCPU.h"
#include "PlayerYOU.h"
#include "PlayerTable.h"

using namespace std;

class Tournament
{
	string randName();
	vector <int> names;
	vector <string> peoples;

	void clearCompany();

	void doNames();

	int chooseRules(vector <rules> pokers);

	int choosePlayers(vector <rules> pokers, int j);

	int chooseTypeOfCompetition();

	void createCompany(Player *company[], int k, string name);

	void saveStatistic(rules rule, int currRes, vector <game> &games, string name, int fileMistakes);

public:
	Tournament();

	void tour(vector <rules> pokers, string name, vector <game> &games, int fileMistakes); //выбрать чемпионат
};