#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "Structures.h"
#include "RulesMaker.h"
#include "Tournament.h"

using namespace std;

class PokerCoordinator
{	
	vector <rules> pokers; //наборы правил, доступные игроку

	vector <game> games; //статистика игрока

	string name;

	void makeName();

	void showStatistic(); //показываем статистику игрока
	
	void readStatistic(string name); //считываем из файла

	int fileMistakes; //количество ошибок в загружаемых файлах для текущего игрока (чтобы не перегружать пользователя сообщениями об ошибках)
	
	int loadName();
		
	void about();

	int startMenu();

	int menu(Tournament tour);

public:

	PokerCoordinator();

	void go();
};