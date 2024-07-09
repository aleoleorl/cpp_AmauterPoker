#include "OneGame.h"

void OneGame::letsSitDownAtTheTable(Player *company[], int pl, rules gameRules, int currFirstPlayer) //подготовка игры
{
	game = 1; //предполагаем, что игра началась

	currentFirstPlayer = currFirstPlayer; //задаём первого игрока раунда

	bank = 0; //предварительно задаём банк

	int y = 0;

	company[pl]->clearHand(); //убираем карты со стола
	
	for (int i = 0; i<pl; i++)
	{
		company[i]->clearHand(); //чистим руки от карт предыдущей игры
		company[i]->clearBet(); //чистим ставку
		if (company[i]->inGame != -2) //у игрока есть деньги, чтобы участвовать в игре
		{
			company[i]->inGame = 1; //никто ещё не пасовал
		}
		if (gameRules.startBet == 1 && i == currentFirstPlayer) //если по правилам ставит только первый игрок (проверка в Tournament, что он платёжеспособен)
		{
			int k = company[i]->makeBet(gameRules.bet);
			curMaxBet = k;//задаём начальную ставку				
			bank += k; //начальный банк
		}
		if (gameRules.startBet == 2) //если по правилам ставят первый и второй игрок
		{			
			if (i == currentFirstPlayer)
			{
				int k = company[i]->makeBet(gameRules.bet/2);
				curMaxBet = k;//задаём начальную ставку				
				bank += k; //начальный банк
				y++;
			}
		}
		if (gameRules.startBet == 3) //если по правилам ставят второй и третий игрок
		{
			if (i == currentFirstPlayer)
			{
				y++;
				if (pl == 2) //всего один соперник, ставки бессмыслены
				{
					y = 3;
				}
			}
		}
		if (gameRules.startBet == 9) //если по правилам ставят все игроки
		{
			int k = company[i]->makeBet(gameRules.bet);
			if (curMaxBet != k)
			{
				curMaxBet = k;//задаём начальную ставку				
			}
			bank += k; //начальный банк
		}
	}

	for (int i = 0; i<pl; i++)
	{
		if (gameRules.startBet == 2) //если по правилам ставят первый и второй игрок
		{
			if (i != currentFirstPlayer && company[i]->inGame>0 && y == 1) //это не первый игрок, он может участвовать в игре и первый игрок уже ставил
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
					curMaxBet = k;//задаём начальную ставку				
					bank += k; //начальный банк
					y++;
				}
			}
		}
		if (gameRules.startBet == 3) //если по правилам ставят второй и третий игрок
		{
			if (i != currentFirstPlayer && company[i]->inGame>0 && y >= 1 && y <= 2) //это не первый игрок, он может участвовать в игре
			{
				int k = 0;
				if (y == 2 && ((i > currentFirstPlayer) || (i == 0 && currentFirstPlayer == pl - 2) || (i == 1 && currentFirstPlayer == pl - 1)))
				{
					cout << "y=" << y << endl;
					k = company[i]->makeBet(gameRules.bet);
					curMaxBet = k;//задаём начальную ставку				
					bank += k; //начальный банк
					y++;
				}
				if ((y == 1) && ((currentFirstPlayer == pl - 1 && i <currentFirstPlayer) || (i > currentFirstPlayer)))
				{
					cout << "y=" << y << endl;
					k = company[i]->makeBet(gameRules.bet / 2);
					curMaxBet = k;//задаём начальную ставку				
					bank += k; //начальный банк
					y++;
				}				
			}
		}
	}

	roundStartBet = 0;//задаём начальную ставку раунда

	roundDeck.Stir(); //перемешиваем карты в колоде

	round = 0;  //задаём текущий раунд
}

void OneGame::allTakeACard(Player *company[], int pl, rules gameRules, int numOfThisTypeCard, int typeOfCard)
{
	deck card;
	for (int i = 0; i<pl; i++)
	{
		if (company[i]->inGame>0 || company[i]->inGame == -1) //если мы в игре
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

void OneGame::prepareMove(Player *company[], int pl, rules gameRules) //подготовка раунда
{
	//раздать карты, если это требуется условиями раунда       
	allTakeACard(company, pl, gameRules, gameRules.turns[round].cardsToPlayerClose, 0); //в закрытую
	allTakeACard(company, pl, gameRules, gameRules.turns[round].cardsToPlayerOpenForMe, 1); //видит только получатель карты
	allTakeACard(company, pl, gameRules, gameRules.turns[round].cardsToPlayerOpen, 2); //в открытую

	takeACard(company[pl], pl, gameRules, gameRules.turns[round].cardsOnTableClose, 0); //на стол в закрытую
	takeACard(company[pl], pl, gameRules, gameRules.turns[round].cardsOnTableOpen, 2); //на стол в открытую        
}

void OneGame::players(Player *company[], int pl, rules gameRules, int turns, int turn) //ходы игроков
{
	int n = 0;
	int currBetMaker = currentFirstPlayer; //текущий последний повышавший ставку
	int i = currBetMaker; //текущий игрок
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
	while (n == 0) //раунд торговли
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
		if (i != currBetMaker) //если круг от первого до повышавшего ещё не пройден
		{
			if (company[i]->inGame == 1)
			{
				system("cls");
				cout << gameRules.name << ".\nGame " << (turn + 1) << "/" << turns << " (round " << (round + 1) << ")\n";
				cout << "Bank: " << bank << "\n\n";
			}
			
			if (company[i]->turn(company, pl, gameRules, round, curMaxBet, currentFirstPlayer, roundStartBet, bank, i) == 1) //ход игрока
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

	if (gameRules.chooseCardChanging == 1 && gameRules.turns[round].cardsCanChangeOnHande>0) //раунд обмена карт
	{
		for (int i = 0; i < pl; i++)
		{
			if (company[i]->inGame>0) //проверяем, чтобы карты могли менять тлоько активные игроки
			{
				company[i]->turnB();
			}
		}
	}
}

void OneGame::transition(Player *company[], int pl, rules gameRules)
{
	//cout << "here";
	//совершить действия после раунда - обменять игрокам карты
	roundStartBet = curMaxBet; //
	//меняем раунд, пока раунды не закончатся в правилах
	round++;
	int sout = 0;
	for (int i = 0; i < pl; i++)
	{
		if (company[i]->inGame>0 || company[i]->inGame==-1) //подсчитываем, сколько игроков ещё в строю
		{
			if (company[i]->inGame > 0)
			{
				sout++;
			}

			//а заодно меняем им карты, если требуется
			if (gameRules.chooseCardChanging == 1)
			{
				vector <int> toCange = company[i]->getCardToChange();
				for (int j = 0; j < toCange.size(); j++)
				{
					deck card;
					card = roundDeck.getOneCard();
					card.viewIt = 0; //видимость остаётся по старой карте
					company[i]->changeCardInHand(card, toCange[j]);
				}
			}
		}
	}
	if (sout <= 1) //если остался один игрок, или ни одного, прекращаем тур
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
	//рассчитываем результаты
	int yourResult = 0;
	vector <double> coeff;
	double great = 0;

	for (int i = 0; i <= pl; i++) //вскрываемся
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
			coeff.push_back(an.getPrioritet(company[i]->showHand(), company[pl]->showHand())); //просчитываем приоритеты
		} else
		{
			vector <deck> temp = company[i]->getPrioritet(company[pl]->showHand(), gameRules); //просчитываем приоритеты, если карты надо выбрать самому
			vector <deck> temp2;
			coeff.push_back(an.getPrioritet(temp, temp2)); //просчитываем приоритеты
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
	for (int i = 0; i < f.size(); i++) //честно делим банк между победителями
	{
		int k = f[i];
		company[k]->getMoney(bank);
	}

	for (int i = 0; i < pl; i++) //исключаем игроков, проигравших деньги
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
	for (int j = 0; j <= pl; j++) //показать текущие карты
	{
		if (company[j]->setName().size() > lenName)
			lenName = company[j]->setName().size();
	}
	lenName += 4; //"(k= )"

	for (int i = 0; i <= pl; i++) //показать текущие карты
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

					if (company[i]->setName() == name) //если это ваша победа
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

const int OneGame::Go(Player *company[], int pl, rules gameRules, int turns, int turn, int currFirstPlayer, string name) //основной класс игры
{ //company - массив игроков, gameRules - набор правил игры

	letsSitDownAtTheTable(company, pl, gameRules, currFirstPlayer);
	
	do
	{
		prepareMove(company, pl, gameRules);
		players(company, pl, gameRules, turns, turn);
		transition(company, pl, gameRules);
	} while (game == 1); //играем, пока есть цикл

	int yourResult;
	yourResult = resultOfTheGame(company, pl, gameRules, turn, turns, name);

	return yourResult;
}