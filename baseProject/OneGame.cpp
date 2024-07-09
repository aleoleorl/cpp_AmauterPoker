#include "OneGame.h"

void OneGame::letsSitDownAtTheTable(Player *company[], int pl, rules gameRules, int currFirstPlayer) //���������� ����
{
	game = 1; //������������, ��� ���� ��������

	currentFirstPlayer = currFirstPlayer; //����� ������� ������ ������

	bank = 0; //�������������� ����� ����

	int y = 0;

	company[pl]->clearHand(); //������� ����� �� �����
	
	for (int i = 0; i<pl; i++)
	{
		company[i]->clearHand(); //������ ���� �� ���� ���������� ����
		company[i]->clearBet(); //������ ������
		if (company[i]->inGame != -2) //� ������ ���� ������, ����� ����������� � ����
		{
			company[i]->inGame = 1; //����� ��� �� �������
		}
		if (gameRules.startBet == 1 && i == currentFirstPlayer) //���� �� �������� ������ ������ ������ ����� (�������� � Tournament, ��� �� ��������������)
		{
			int k = company[i]->makeBet(gameRules.bet);
			curMaxBet = k;//����� ��������� ������				
			bank += k; //��������� ����
		}
		if (gameRules.startBet == 2) //���� �� �������� ������ ������ � ������ �����
		{			
			if (i == currentFirstPlayer)
			{
				int k = company[i]->makeBet(gameRules.bet/2);
				curMaxBet = k;//����� ��������� ������				
				bank += k; //��������� ����
				y++;
			}
		}
		if (gameRules.startBet == 3) //���� �� �������� ������ ������ � ������ �����
		{
			if (i == currentFirstPlayer)
			{
				y++;
				if (pl == 2) //����� ���� ��������, ������ �����������
				{
					y = 3;
				}
			}
		}
		if (gameRules.startBet == 9) //���� �� �������� ������ ��� ������
		{
			int k = company[i]->makeBet(gameRules.bet);
			if (curMaxBet != k)
			{
				curMaxBet = k;//����� ��������� ������				
			}
			bank += k; //��������� ����
		}
	}

	for (int i = 0; i<pl; i++)
	{
		if (gameRules.startBet == 2) //���� �� �������� ������ ������ � ������ �����
		{
			if (i != currentFirstPlayer && company[i]->inGame>0 && y == 1) //��� �� ������ �����, �� ����� ����������� � ���� � ������ ����� ��� ������
			{
				if ((currentFirstPlayer == pl - 1 && i == 0) || (i>currentFirstPlayer))
				{
					int k = 0;
					if (pl < 3)
					{
						k = company[i]->makeBet(gameRules.bet / 2);
					}
					else
					{
						k = company[i]->makeBet(gameRules.bet);
					}
					curMaxBet = k;//����� ��������� ������				
					bank += k; //��������� ����
					y++;
				}
			}
		}
		if (gameRules.startBet == 3) //���� �� �������� ������ ������ � ������ �����
		{
			if (i != currentFirstPlayer && company[i]->inGame>0 && y >= 1 && y <= 2) //��� �� ������ �����, �� ����� ����������� � ����
			{
				int k = 0;
				if (y == 2 && ((i > currentFirstPlayer) || (i == 0 && currentFirstPlayer == pl - 2) || (i == 1 && currentFirstPlayer == pl - 1)))
				{
					cout << "y=" << y << endl;
					k = company[i]->makeBet(gameRules.bet);
					curMaxBet = k;//����� ��������� ������				
					bank += k; //��������� ����
					y++;
				}
				if ((y == 1) && ((currentFirstPlayer == pl - 1 && i <currentFirstPlayer) || (i > currentFirstPlayer)))
				{
					cout << "y=" << y << endl;
					k = company[i]->makeBet(gameRules.bet / 2);
					curMaxBet = k;//����� ��������� ������				
					bank += k; //��������� ����
					y++;
				}				
			}
		}
	}

	roundStartBet = 0;//����� ��������� ������ ������

	roundDeck.Stir(); //������������ ����� � ������

	round = 0;  //����� ������� �����
}

void OneGame::allTakeACard(Player *company[], int pl, rules gameRules, int numOfThisTypeCard, int typeOfCard)
{
	deck card;
	for (int i = 0; i<pl; i++)
	{
		if (company[i]->inGame>0 || company[i]->inGame == -1) //���� �� � ����
		{
			int j = numOfThisTypeCard;
			while (j > 0)
			{
				card = roundDeck.getOneCard();
				card.viewIt = typeOfCard;
				company[i]->getOneCard(card);
				j--;
			}
		}
	}
}

void OneGame::takeACard(Player *one, int pl, rules gameRules, int numOfThisTypeCard, int typeOfCard)
{
	deck card;
	for (int i = 0; i<numOfThisTypeCard; i++)
	{
		card = roundDeck.getOneCard();
		card.viewIt = typeOfCard;
		one->getOneCard(card);
	}
}

void OneGame::prepareMove(Player *company[], int pl, rules gameRules) //���������� ������
{
	//������� �����, ���� ��� ��������� ��������� ������       
	allTakeACard(company, pl, gameRules, gameRules.turns[round].cardsToPlayerClose, 0); //� ��������
	allTakeACard(company, pl, gameRules, gameRules.turns[round].cardsToPlayerOpenForMe, 1); //����� ������ ���������� �����
	allTakeACard(company, pl, gameRules, gameRules.turns[round].cardsToPlayerOpen, 2); //� ��������

	takeACard(company[pl], pl, gameRules, gameRules.turns[round].cardsOnTableClose, 0); //�� ���� � ��������
	takeACard(company[pl], pl, gameRules, gameRules.turns[round].cardsOnTableOpen, 2); //�� ���� � ��������        
}

void OneGame::players(Player *company[], int pl, rules gameRules, int turns, int turn) //���� �������
{
	int n = 0;
	int currBetMaker = currentFirstPlayer; //������� ��������� ���������� ������
	int i = currBetMaker; //������� �����
	if (round != 0)
	{
		currBetMaker = -1;
		i--;
	}

	if (round == 0)
	{
		//currBetMaker = -1;

		if (gameRules.startBet == 2 || gameRules.startBet == 3)
		{
			int now = 0;
			if (gameRules.startBet == 3)
				now = 2;
			if (gameRules.startBet == 2)
				now = 1;
			i += now;
			while (now != 0)
			{
				if (i >= pl)
				{
					i = 0;
				}
				if (company[i]->inGame > 0)
				{
					now--;
				}
			}
		}
	}

	int r = 0;
	while (n == 0) //����� ��������
	{
		if (i < pl)
		{
			i++;
		}
		if (i == pl)
		{
			i = 0;
			r = 1;
			if (r == 1 && currBetMaker == -1)
			{
				currBetMaker = currentFirstPlayer;
			}
		}
		if (i != currBetMaker) //���� ���� �� ������� �� ����������� ��� �� �������
		{
			if (company[i]->inGame == 1)
			{
				system("cls");
				cout << gameRules.name << ".\nGame " << (turn + 1) << "/" << turns << " (round " << (round + 1) << ")\n";
				cout << "Bank: " << bank << "\n\n";
			}
			
			if (company[i]->turn(company, pl, gameRules, round, curMaxBet, currentFirstPlayer, roundStartBet, bank, i) == 1) //��� ������
			{
				currBetMaker = i;
			}
		}
		else
		{
			n = 1;
		}
	}
		
	//cout << "here or ";

	if (gameRules.chooseCardChanging == 1 && gameRules.turns[round].cardsCanChangeOnHande>0) //����� ������ ����
	{
		for (int i = 0; i < pl; i++)
		{
			if (company[i]->inGame>0) //���������, ����� ����� ����� ������ ������ �������� ������
			{
				company[i]->turnB();
			}
		}
	}
}

void OneGame::transition(Player *company[], int pl, rules gameRules)
{
	//cout << "here";
	//��������� �������� ����� ������ - �������� ������� �����
	roundStartBet = curMaxBet; //
	//������ �����, ���� ������ �� ���������� � ��������
	round++;
	int sout = 0;
	for (int i = 0; i < pl; i++)
	{
		if (company[i]->inGame>0 || company[i]->inGame==-1) //������������, ������� ������� ��� � �����
		{
			if (company[i]->inGame > 0)
			{
				sout++;
			}

			//� ������ ������ �� �����, ���� ���������
			if (gameRules.chooseCardChanging == 1)
			{
				vector <int> toCange = company[i]->getCardToChange();
				for (int j = 0; j < toCange.size(); j++)
				{
					deck card;
					card = roundDeck.getOneCard();
					card.viewIt = 0; //��������� ������� �� ������ �����
					company[i]->changeCardInHand(card, toCange[j]);
				}
			}
		}
	}
	if (sout <= 1) //���� ������� ���� �����, ��� �� ������, ���������� ���
	{
		round = gameRules.turns.size();
	}
	if (round == gameRules.turns.size())
	{
		game = 0;
	}
	if (round != gameRules.turns.size())
	{
		cout << "\nNext round";
		getch();
	}
}

int OneGame::resultOfTheGame(Player *company[], int pl, rules gameRules, int turn, int turns, string name)
{
	//������������ ����������
	int yourResult = 0;
	vector <double> coeff;
	double great = 0;

	for (int i = 0; i <= pl; i++) //�����������
	{
		company[i]->openCards();
	}

//	cout << "Over finish";
//	getch();
	vector <int> f;
	for (int i = 0; i < pl; i++)
	{
		if (gameRules.fromHand == 0)
		{
			coeff.push_back(an.getPrioritet(company[i]->showHand(), company[pl]->showHand())); //������������ ����������
		} else
		{
			vector <deck> temp = company[i]->getPrioritet(company[pl]->showHand(), gameRules); //������������ ����������, ���� ����� ���� ������� ������
			vector <deck> temp2;
			coeff.push_back(an.getPrioritet(temp, temp2)); //������������ ����������
			//cout << "\ncoeff=" << coeff[coeff.size() - 1] << endl;
			//getch();
		}
		if (coeff[coeff.size() - 1]>great)
		{
			great = coeff[coeff.size() - 1];
			f.erase(f.begin(), f.end());
			f.push_back(i);
			continue;
		}
		if (coeff[coeff.size() - 1] == great)
		{
			f.push_back(i);
		}
	}

	bank /= f.size();
	for (int i = 0; i < f.size(); i++) //������ ����� ���� ����� ������������
	{
		int k = f[i];
		company[k]->getMoney(bank);
	}

	for (int i = 0; i < pl; i++) //��������� �������, ����������� ������
	{
		if (company[i]->inGame != -1 && company[i]->setMoney() == 0)
		{
			company[i]->inGame = -2;
		}
	}

	system("cls");
	cout << gameRules.name << ".\nGame " << (turn + 1) << "/" << turns << "\n";
	if (f.size()>1)
	{
		cout << "Bank to every winner: " << bank << "\n\n";
	} else
	{
		cout << "Bank to winner: " << bank << "\n\n";
	}

	int lenName = 0;
	for (int j = 0; j <= pl; j++) //�������� ������� �����
	{
		if (company[j]->setName().size() > lenName)
			lenName = company[j]->setName().size();
	}
	lenName += 4; //"(k= )"

	for (int i = 0; i <= pl; i++) //�������� ������� �����
	{
		company[i]->showCards(i, currentFirstPlayer, -1, lenName);
		if (i != pl)
		{
			cout << an.combination(coeff[i]);
			for (int j = 0; j < f.size(); j++)
			{
				if (i == f[j])
				{
					cout << "(win)";

					if (company[i]->setName() == name) //���� ��� ���� ������
					{
						yourResult = 1;
					}
				}
			}
		}
		cout << endl;
	}
	getch();
	return yourResult;
}

OneGame::OneGame()
{
	game = 0;
	round = 0;
	currentFirstPlayer = 0;
	curMaxBet = 0;
}

const int OneGame::Go(Player *company[], int pl, rules gameRules, int turns, int turn, int currFirstPlayer, string name) //�������� ����� ����
{ //company - ������ �������, gameRules - ����� ������ ����

	letsSitDownAtTheTable(company, pl, gameRules, currFirstPlayer);
	
	do
	{
		prepareMove(company, pl, gameRules);
		players(company, pl, gameRules, turns, turn);
		transition(company, pl, gameRules);
	} while (game == 1); //������, ���� ���� ����

	int yourResult;
	yourResult = resultOfTheGame(company, pl, gameRules, turn, turns, name);

	return yourResult;
}