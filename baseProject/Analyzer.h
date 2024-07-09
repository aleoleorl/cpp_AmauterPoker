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
	10 Royal Flush - ����-����
	9 Straight Flush - �����-����
	8 Four of a Kind - ���� 
	7 Full House - ���-����
	6 Flush - ���� 
	5 Straight - ����� 
	4 Three of a Kind - ������ ��� ���
	3 Two-pair - ��� ����
	2 One-pair - ����
	1 High-card - ������ �����	
	*/

	Analyzer();

	double getPrioritet(vector <deck> hero, vector <deck> table);
};