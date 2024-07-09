#include "PlayerYOU.h"

PlayerYOU::PlayerYOU()
{
}

int PlayerYOU::turn(Player *company[], int pl, rules gameRules, int round, int &curMaxBet, int currentFirstPlayer, int roundStartBet, int &bank, int myI)
{
	int bt = 0;
	if (inGame == 1) //если есть возможность участвовать
	{
		int lenName = 0;
		int lenTemp = 0;
		for (int j = 0; j <= pl; j++) //показать текущие карты
		{
			lenTemp = company[j]->setName().size();
			if (j == currentFirstPlayer)
			{
				lenTemp += 4; //"(k= )"
			}
			if (lenTemp > lenName)
			{
				lenName = lenTemp;
			}
		}

		for (int j = 0; j <= pl; j++) //показать текущие карты
		{
			company[j]->showCards(j, currentFirstPlayer, myI, lenName);
			cout << endl;
		}
		cout << "\nChoose:" << endl;
		if (myBet < curMaxBet)
		{
			cout << "5 - call;\n";
			if (curMaxBet - roundStartBet < gameRules.maxBet)
			{
				cout << "7 - raise\n";
			}
			cout << "9 - fold; " << endl;
		}
		else
		{
			cout << "1 - check;\n7 - bet;\n9 - fold" << endl;
		}

		int n = 0;
		char j = 0;
		while (n == 0)
		{
			j = getch();
			if (myBet < curMaxBet)
			{
				if (j == '7' && curMaxBet - roundStartBet < gameRules.maxBet)
				{
					n = 1;
				}
				if (j == '5' || j == '9')
				{
					n = 1;
				}
			}
			if ((myBet == curMaxBet) && (j == '1' || j == '7' || j == '9'))
			{
				n = 1;
			}
		}

		if (j == '9')
		{
			inGame = 0;
			clearHand();
		}
		if (j == '1')
		{
		}
		if (j == '5')
		{
			int k = makeBet(curMaxBet - myBet);
			bank += k; //поддержали
		}
		if (j == '7')
		{
			int k = makeBet(curMaxBet - myBet);
			bank += k;
			k = makeBet(gameRules.bet);
			bank += k;
			curMaxBet += k;
			bt = 1;
		}
	}
	return bt;
}

void PlayerYOU::turnB()
{
	system("cls");
	showCards(-1, -2, -3, 0);
	cout << endl;

	int num = -1;
	cout << "How many cards do you want to change?\n";

	while (num < 0 || num > onHand.size())
	{
		cin >> num;
	}
	if (num == onHand.size()) //все меняем
	{
		for (int i = 0; i < onHand.size(); i++)
		{
			toCange.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < num; i++) //выбираем изменяемые карты
		{
			cout << "Choose number of " << (i + 1) << " changing card (1-" << onHand.size() << ")\n";
			int notIt = 0;
			int u;
			while (notIt == 0)
			{
				cin >> u;
				u--;
				if (u >= 0 && u < onHand.size()) //если номер не выходит из диапазона
				{
					notIt = 1;
					for (int j = 0; j < toCange.size(); j++)
					{
						if (toCange[j] == u) //мы нашли, что такюу карту уже выбирали ранее
						{
							notIt = 0;
						}
					}
				}
			}
			toCange.push_back(u);
		}
	}
}

vector <deck> PlayerYOU::getPrioritet(vector <deck> table, rules gameRules)
{
	if (inGame == 0 || inGame == -2)
	{
		vector <deck> tempBest;
		return tempBest;
	}

	system("cls");
	cout << "Your cards:" << endl;
	showCards(-1, -2, -3, 0);
	cout << "\nTable:";	
	for (int i = 0; i<table.size(); i++)
	{
		if (table[i].viewIt == 0)
		{
			cout << "## ";
		}
		if (table[i].viewIt == 1 || table[i].viewIt == 2)
		{
			showCard(table[i]);
		}
	}
	cout << endl;

	int num = gameRules.fromHand;
	cout << "\nChoose " << num << " cards from your hand.\n";

	vector <deck> temp;

	toCange.erase(toCange.begin(), toCange.end());

	for (int i = 0; i < num; i++) //выбираем карты из руки
	{
		cout << "Choose number of " << (i + 1) << " card (1-" << onHand.size() << "):\n";
		int notIt = 0;
		int u;
		while (notIt == 0)
		{
			cin >> u;
			u--;
			if (u >= 0 && u < onHand.size()) //если номер не выходит из диапазона
			{
				notIt = 1;
				for (int j = 0; j < toCange.size(); j++)
				{
					if (toCange[j] == u) //мы нашли, что такую карту уже выбирали ранее
					{
						notIt = 0;
					}
				}
			}
		}
		toCange.push_back(u);
		temp.push_back(onHand[u]);
	}

	num = 5 - num;
	toCange.erase(toCange.begin(), toCange.end());
	cout << "\nChoose " << num << " cards from the table.\n";
	
	for (int i = 0; i < num; i++) //выбираем карты со стола
	{
		cout << "Choose number of " << (i + 1) << " card (1-" << table.size() << ")\n";
		int notIt = 0;
		int u;
		while (notIt == 0)
		{
			cin >> u;
			u--;
			if (u >= 0 && u < table.size()) //если номер не выходит из диапазона
			{
				notIt = 1;
				for (int j = 0; j < toCange.size(); j++)
				{
					if (toCange[j] == u) //мы нашли, что такую карту уже выбирали ранее
					{
						notIt = 0;
					}
				}
			}
		}
		toCange.push_back(u);
		temp.push_back(table[u]);
	}

	return temp;
}

void PlayerYOU::showCards(int iAm, int currIs, int curPlayer, int lenName)
{
	int len = lenName;

	if (iAm == curPlayer)
	{
		cout << ">> ";
	}
	if (iAm == currIs)
	{
		cout << "(k) ";
		len -= 4;
	}

	cout << chara.name;

	if (chara.name.size()<len)
	for (int i = 0; i < len - chara.name.size(); i++)
	{
		cout << " ";
	}
	
	cout << " (" << chara.money << "$)" << ":";
	cout << " bet = " << myBet << "$ : ";
	for (int i = 0; i<onHand.size(); i++)
	{
		if (onHand[i].viewIt == 0)
		{
			cout << "## ";
		}
		if (onHand[i].viewIt == 1 || onHand[i].viewIt == 2)
		{
			showCard(onHand[i]);
		}
	}
}