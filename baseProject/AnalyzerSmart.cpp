#include "AnalyzerSmart.h"

int AnalyzerSmart::sum(int money, int curMaxBet, int myBet) //проверяем, хватает ли денег на ставку
{
	if (money >= curMaxBet - myBet)
	{
		return 2;
	}
	else
	{
		return 5;
	}
}

int AnalyzerSmart::mult(int money, int curMaxBet, int myBet, int roundStartBet, rules gameRules, int res) //проверяем, хватает ли денег на ставку
{
	if (res == 5 || money < gameRules.bet) //уже все деньги вложены или их осталось мало
	{
		return 5;
	}
	if (roundStartBet + gameRules.maxBet>curMaxBet)
	{
		if (curMaxBet == myBet)
		{
			return 4;
		}
		else
		{
			return 6;
		}
	}
	else
	{
		return 2;
	}
}

double AnalyzerSmart::cardsRate(vector <double> coeff, int pl, int myI)
{
	double rate1Cost = (double)1 / pl; //цена единицы преимущества любого другого игрока над текущим
	double rate1 = 1;
	for (int i = 0; i < pl; i++)
	{
		if (i == myI) continue;
		if (coeff[myI] - coeff[i] < 0)
		{
			if (coeff[myI] - coeff[i] < 1)
			{
				rate1 -= rate1Cost;
			}
			else
			{
				rate1 -= (coeff[i] - coeff[myI]) / pl;
			}
		}
	}
	return rate1;
}

double AnalyzerSmart::potentialRate(rules gameRules, int round)
{
	int allCards = 0;
	int lostCards = 0;
	for (int i = 0; i < gameRules.turns.size(); i++)
	{
		if (i >= round)
		{
			lostCards += gameRules.turns[i].cardsCanChangeOnHande;
		}
		if (i > round)
		{
			lostCards += gameRules.turns[i].cardsOnTableOpen;
			lostCards += gameRules.turns[i].cardsToPlayerOpenForMe;
			lostCards += gameRules.turns[i].cardsOnTableOpen;
		}
		lostCards += gameRules.turns[i].cardsOnTableClose;
		lostCards += gameRules.turns[i].cardsToPlayerClose;

		allCards += gameRules.turns[i].cardsCanChangeOnHande;
		allCards += gameRules.turns[i].cardsOnTableClose;
		allCards += gameRules.turns[i].cardsOnTableOpen;
		allCards += gameRules.turns[i].cardsToPlayerClose;
		allCards += gameRules.turns[i].cardsToPlayerOpen;
		allCards += gameRules.turns[i].cardsToPlayerOpenForMe;
	}
	return (double)lostCards / allCards;
}

AnalyzerSmart::AnalyzerSmart()
{
	risker = (double)(rand() % 100) / 100; //склонность к неоправданному риску
}

vector <deck> getAvailanleCards(vector <deck> onHand)
{
	vector <deck> myDeck;
	for (int i = 0; i < onHand.size(); i++)
	{
		if (onHand[i].viewIt == 1 || onHand[i].viewIt == 2)
		{
			myDeck.push_back(onHand[i]);
		}
	}
	return myDeck;
}

vector <int> AnalyzerSmart::toChange(vector <deck> onHand)
{
	vector <int> temp;
	
	vector <deck> myDeck = getAvailanleCards(onHand); //формируем карты в последовательность для разбора

	//находим текущую комбинацию карт
	coefinator1(myDeck); 
	double x = coefinator2();

	for (int i = 0; i < myDeck.size(); i++)
	{
		vector <deck> nocard;
		nocard.erase(nocard.begin(), nocard.end());
		for (int j = 0; j < myDeck.size(); j++)
		{
			if (i != j)
			{
				nocard.push_back(myDeck[j]);
			}
		}
		coefinator1(nocard);
		double y = coefinator2();
		if (y == x)
		{
			temp.push_back(i); //добавляем в последовательность карту, изменение которой на имеющуюся комбинацию не повлияет
		}
	}

	int i = 0;
	while (i < temp.size())
	{
		int y = rand() % 5;
		if (y < 3)
		{
			temp.erase(temp.begin() + i);
			i--;
		}
		i++;
	}

	return temp;
}

int AnalyzerSmart::decision(Player *company[], int pl, rules gameRules, int round, int curMaxBet, int roundStartBet, int myBet, int myI)
{
	vector <double> coeff;
	for (int i = 0; i < pl; i++)
	{
		coeff.push_back(getPrioritet(company[i]->showHand(), company[pl]->showHand()));
		//cout << i << ":" << coeff[i] << endl;
	}

	//подсчитываем коэффициенты:

	//текущие карты
	double rate1 = cardsRate(coeff, pl, myI);
	//cout << "rate1=" << rate1 << endl;

	//возможность получить ещё карты
	double rate2 = potentialRate(gameRules, round);
	//cout << "rate2=" << rate2 << endl;

	//cout << "risker=" << risker << endl;
	int res = 1;
	
	//делаем решение:

	//поддерживать ли ставку
	if (myBet < curMaxBet) //если наша ставка меньше текущей ставки
	{
		double r = rate1*0.5 + rate2*0.3 + risker*0.2;
		//cout << "r=" << r << endl;

		if (r < 0.2 - risker*0.15)
		{
			int k = rand() % 10;
			if (k >= 8) //не пасуем
			{
				res = sum(company[myI]->setMoney(), curMaxBet, myBet);
			}
		}
		if (r < 0.5 - risker*0.15 && r >= 0.2 - risker*0.15)
		{
			int k = rand() % 10;
			if (k >= 4) //не пасуем
			{
				res = sum(company[myI]->setMoney(), curMaxBet, myBet);
			}
		}
		if (r < 0.8 - risker*0.15 && r >= 0.5 - risker*0.15)
		{
			int k = rand() % 10;
			if (k >= 2) //не пасуем
			{
				res = sum(company[myI]->setMoney(), curMaxBet, myBet);
			}
		}
		if (r >= 0.8 - risker*0.15)
		{
			res = sum(company[myI]->setMoney(), curMaxBet, myBet);
		}
	}
	else
	{
		res = 3;
	}

	//повышать ли ставку
	if (res != 1)
	{
		double r = rate1*0.6 + rate2*0.1 + risker*0.3;
		if (r >= 0.9)
		{
			int k = rand() % 10;
			if (k >= 2) //увеличиваем
			{
				res = mult(company[myI]->setMoney(), curMaxBet, myBet, roundStartBet, gameRules, res);
			}
		}
		if (r >= 0.5 && r < 0.9)
		{
			int k = rand() % 10;
			if (k >= 6) //увеличиваем
			{
				res = mult(company[myI]->setMoney(), curMaxBet, myBet, roundStartBet, gameRules, res);
			}
		}
		if (r < 0.5)
		{
			int k = rand() % 10;
			if (k >= 8) //увеличиваем
			{
				res = mult(company[myI]->setMoney(), curMaxBet, myBet, roundStartBet, gameRules, res);
			}
		}
	}
	/*res == 1 " fold" << endl;
	res == 2 " call" << endl;
	res == 3 " check" << endl;
	res == 4 " bet" << endl;
	res == 5 " all-in" << endl;
	res == 6 " raise" << endl;
	*/

	return res;
}