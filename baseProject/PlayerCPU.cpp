#include "PlayerCPU.h"

PlayerCPU::PlayerCPU()
{
}

int PlayerCPU::turn(Player *company[], int pl, rules gameRules, int round, int &curMaxBet, int currentFirstPlayer, int roundStartBet, int &bank, int myI) //ход компа
{
	int bt = 0; //повышает ли ставку

	if (inGame == 1) //если есть возможность участвовать
	{
		int res = an.decision(company, pl, gameRules, round, curMaxBet, roundStartBet, myBet, myI);

		//часть к исполнению
		if (res == 1)
		{
			clearHand();
			inGame = 0;
		}
		if (res == 2)
		{
			int k = makeBet(curMaxBet - myBet);
			bank += k;
		}
		if (res == 3)
		{
		}
		if (res == 4)
		{
			if (curMaxBet > myBet) //излишняя проверка на случай ошибки в коде
			{
				int k = makeBet(curMaxBet - myBet);
				bank += k;
			}
			if (curMaxBet == myBet)
			{
				int k = makeBet(gameRules.bet);
				bank += k;
				curMaxBet += k;
				bt = 1;
			}
		}
		if (res == 5)
		{
			int k = makeBet(curMaxBet - myBet);
			bank += k;
			if (curMaxBet == myBet) //если денег поддержать ставку хватило, но не хватило поднять
			{
				int k = makeBet(gameRules.bet);
				bank += k;
				curMaxBet += k;
				bt = 1;
			}
		}
		if (res == 6)
		{
			if (curMaxBet > myBet)
			{
				int k = makeBet(curMaxBet - myBet);
				bank += k;
			}
			if (curMaxBet == myBet)
			{
				int k = makeBet(gameRules.bet);
				bank += k;
				curMaxBet += k;
				bt = 1;
			}
		}

		int lenName = 0;
		int lenTemp=0;
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
		cout << endl;

		//часть к показу
		if (res == 1)
		{
			cout << chara.name << " fold" << endl;
		}
		if (res == 2)
		{
			cout << chara.name << " call" << endl;
		}
		if (res == 3)
		{
			cout << chara.name << " check" << endl;
		}
		if (res == 4)
		{
			cout << chara.name << " bet" << endl;
		}
		if (res == 5)
		{
			cout << chara.name << " all-in" << endl;
		}
		if (res == 6)
		{
			cout << chara.name << " raise" << endl;
		}

		cout << "Next?";
		int j = getch();
	}
	return bt;
}

void PlayerCPU::turnB()
{
	toCange = an.toChange(onHand);
}

vector <deck> PlayerCPU::getPrioritet(vector <deck> tableDeck, rules gameRules)
{
	if (inGame == 0 || inGame == -2)
	{
		vector <deck> tempBest;
		return tempBest;
	}

	vector <deck> tempBest;
	double bestCoeff = 0;
	
	vector <int> hand;
	for (int i = 0; i < gameRules.fromHand; i++)
	{
		hand.push_back(0);
	}

	int y = hand.size() - 1;

	while (y >= 0)
	{
		//часть первая - меняем значения
		hand[y]++;
		for (int j = hand.size() - 1; j >= 0; j--)
		{
			if (hand[j] == onHand.size())
			{
				if (j > 0)
				{
					hand[j - 1]++;
					for (int k = j; k < hand.size(); k++)
					{
						hand[k] = 0;
					}
				} else
				{
					y = -1;
				}
			}
		}
		if (y == -1)
		{
			break;
		}

		//часть вторая - проверяем, что значения разные
		int x = 0; // -1 bad, -2 good
		int z = 1;
		while (x != -1 && x != -2)
		{
			if (hand[x] == hand[z])
			{
				x = -1;
				break;
			}
			z++;
			if (z == hand.size())
			{
				x++;
				z = x + 1;
				if (z == hand.size())
				{
					x = -2;
					break;
				}
			}
		}

		//часть третья - если всё хорошо - делаем всё то же для карт со стола
		if (x == -2)
		{
			vector <int> table;
			for (int i = 0; i < 5-gameRules.fromHand; i++)
			{
				table.push_back(0);
			}

			int y = table.size() - 1;
			while (y >= 0)
			{
				//часть четвёртая - меняем значения со стола
				table[y]++;
				for (int j = table.size() - 1; j >= 0; j--)
				{
					if (table[j] == tableDeck.size())
					{
						if (j > 0)
						{
							table[j - 1]++;
							for (int k = j; k < table.size(); k++)
							{
								table[k] = 0;
							}
						}
						else
						{
							y = -1;
						}
					}
				}
				if (y == -1)
				{
					break;
				}
				//часть пятая - проверяем, что значения карт стола разные
				int x = 0; // -1 bad, -2 good
				int z = 1;
				while (x != -1 && x != -2)
				{
					if (table[x] == table[z])
					{
						x = -1;
						break;
					}
					z++;
					if (z == table.size())
					{
						x++;
						z = x + 1;
						if (z == table.size())
						{
							x = -2;
							break;
						}
					}
				}
				//часть шестая - если всё хорошо - рассчитываем коэффициент набора
				if (x == -2)
				{
					vector <deck> temp;
					vector <deck> tempNull;
					for (int i = 0; i < hand.size(); i++)
					{
						temp.push_back(onHand[hand[i]]);
					}
					for (int i = 0; i < table.size(); i++)
					{
						temp.push_back(tableDeck[table[i]]);
					}
					double u = an.getPrioritet(temp, tempNull);
					if (u > bestCoeff)
					{
						bestCoeff = u;
						tempBest = temp;
					}
				}
			}
		}
	}
	return tempBest;
}

void PlayerCPU::showCards(int iAm, int currIs, int curPlayer, int lenName)
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
		if (onHand[i].viewIt == 0 || onHand[i].viewIt == 1)
		{
			cout << "## ";
		}
		if (onHand[i].viewIt == 2)
		{
			showCard(onHand[i]);
		}
	}
}