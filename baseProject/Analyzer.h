#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Structures.h"

using namespace std;

class Analyzer
{
protected:
	struct dk
	{
		int number;
		int suit;
		int cout=0;
	};
	struct N
	{
		vector <dk> structi;
	};

	vector <dk> combo1;
	vector <dk> combo2;
	vector <N> combo3;

	void f1(vector<N> &n, int curr, vector <deck> myDeck);

	double coefinator1(vector <deck> myDeck);

	double coefinator2();
		
public:
	/*
	10 Royal Flush - Роял-флеш
	9 Straight Flush - Стрит-флеш
	8 Four of a Kind - Каре 
	7 Full House - Фул-Хаус
	6 Flush - Флеш 
	5 Straight - Стрит 
	4 Three of a Kind - Тройка или Сет
	3 Two-pair - Две пары
	2 One-pair - Пара
	1 High-card - Высшая карта	
	*/

	Analyzer();

	double getPrioritet(vector <deck> hero, vector <deck> table);
};