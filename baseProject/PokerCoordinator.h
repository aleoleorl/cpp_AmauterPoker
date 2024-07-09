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
	vector <rules> pokers; //������ ������, ��������� ������

	vector <game> games; //���������� ������

	string name;

	void makeName();

	void showStatistic(); //���������� ���������� ������
	
	void readStatistic(string name); //��������� �� �����

	int fileMistakes; //���������� ������ � ����������� ������ ��� �������� ������ (����� �� ����������� ������������ ����������� �� �������)
	
	int loadName();
		
	void about();

	int startMenu();

	int menu(Tournament tour);

public:

	PokerCoordinator();

	void go();
};