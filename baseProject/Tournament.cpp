#include "Tournament.h"

void Tournament::clearCompany()
{
	names.erase(names.begin(), names.end());
}

void Tournament::doNames()
{
	peoples.push_back("Barack Obama");
	peoples.push_back("Gaius Julius Caesar");
	peoples.push_back("George Bush");
	peoples.push_back("Angelina Merkel");
	peoples.push_back("Queen Elizabeth II");
	peoples.push_back("Bruce Willis");
	peoples.push_back("Angelina Jolie");
	peoples.push_back("Chuck Norris");
	peoples.push_back("Gillian Anderson");
	peoples.push_back("Johnny Depp");
	peoples.push_back("Madonna");
	peoples.push_back("Bill Murray");
	peoples.push_back("Elvis Presley");
	peoples.push_back("Sir Elton John");
	peoples.push_back("Whitney Houston");
	peoples.push_back("Stephen Hawking");
	peoples.push_back("Albert Einstein");
	peoples.push_back("Sir Isaac Newton");
	peoples.push_back("Gottfried von Leibniz");
	peoples.push_back("Ernst Mach");
	peoples.push_back("Neil Armstrong");
	peoples.push_back("Sergey Korolev");
	peoples.push_back("Wernher von Braun");
	peoples.push_back("Elon Musk");
	peoples.push_back("Gomez Addams");
	peoples.push_back("Mysterious Stranger");
}


string Tournament::randName()
{	
	int s = -1;
	while (s < 0)
	{
		s = rand() % peoples.size();
		for (int j = 0; j < names.size(); j++)
		{
			if (names[j] == s)
			{
				s = -1;
				break;
			}
		}
	}
	names.push_back(s);
	return peoples[s];
}

int Tournament::chooseRules(vector <rules> pokers)
{	
	for (int i = 0; i < pokers.size(); i++)
	{
		cout << "\"" << pokers[i].name << "\"" << endl;
		cout << pokers[i].rule << endl;
		cout << endl;
	}

	cout << "\nChoose your rules:\n\n";
	for (int i = 0; i < pokers.size(); i++)
	{
		cout << (i+1) << ") " << pokers[i].name << endl;
		cout << endl;
	}
	int j = -1; //номер выбранных правил
	while (j<1 || j>pokers.size())
	{
		cout << "(?) ";
		cin >> j;
	}
	return --j;
}

int Tournament::choosePlayers(vector <rules> pokers, int j)
{
	cout << "Choose number of your opponents (1-" << pokers[j].maxPlayers << "):\n\n";
	int k = -1; //количество игроков
	while (k<0 || k> pokers[j].maxPlayers)
	{
		cout << "(?) ";
		cin >> k;
	}
	k++;
	return k;
}

int Tournament::chooseTypeOfCompetition()
{
	cout << "Choose type of game:\n1 - one game\n2 - tournament (15 games)\n3 - infinity\n";
	int u = -1;
	while (u<1 || u> 3)
	{
		cout << "(?) ";
		cin >> u;
	}
	if (u == 2)
	{
		return 15;
	}
	if (u == 3)
	{
		return 9999999;
	}
	return u;
}

void Tournament::createCompany(Player *company[], int k, string name)
{
	int kk = rand() % k;
	for (int i = 0; i < k; i++)
	{
		if (kk != i)
		{
			string h;
			h = randName();
			PlayerCPU *b = new PlayerCPU;
			b->getCharas(20000, h);
			company[i] = { b };
		}
		else
		{
			PlayerYOU *a = new PlayerYOU;
			a->getCharas(20000, name);
			company[i] = { a };
		}
	}

	PlayerTable *o = new PlayerTable;
	o->getCharas(500, "table");
	company[k] = { o };
}

void Tournament::saveStatistic(rules rule, int currRes, vector <game> &games, string name, int fileMistakes)
{
	char mystring[10000] = "";
	int y = 0;
	for (int i = 0; i < games.size(); i++) //ищем текущую игру (если есть, конечно)
	{
		if (games[i].name == rule.name)
		{
			games[i].games++;
			games[i].wins += currRes;
			y = 1;
			break;
		}
	}
	if (y == 0) //если такой игры ещё не существует, создаём её
	{
		game one;
		one.name = rule.name;
		one.games = 1;
		one.wins = currRes;
		games.push_back(one);
	}

	for (int i = 0; i < games.size(); i++) //готовим строку с данными для передачи в файл
	{
		strcat(mystring, "[");
		strcat(mystring, games[i].name.c_str());
		strcat(mystring, "=");
		char* s = new char[6];
		itoa(games[i].games, s, 10);
		strcat(mystring, s);
		strcat(mystring, "+");
		itoa(games[i].wins, s, 10);
		strcat(mystring, s);
		strcat(mystring, "]");
		delete s;
	}

	char* s = new char[110];
	strcpy(s, name.c_str());
	strcat(s, ".app.txt");

	FILE * f;
	f = fopen(s, "wb");
	if (f == NULL)
	{
		if (fileMistakes == 0)
		{
			cout << "Sorry. Your statistics may be not correct working this time\n";
			getch();
		}
	}
	else
	{
		fputs(mystring, f);
		fclose(f);
	}
}

Tournament::Tournament()
{
	doNames();
}

void Tournament::tour(vector <rules> pokers, string name, vector <game> &games, int fileMistakes) //выбрать чемпионат
{
	int j = chooseRules(pokers); //выбираем правила

	system("cls");
	cout << pokers[j].name << endl;
	cout << endl;
	int k = choosePlayers(pokers, j); //выбираем число соперников

	system("cls");
	cout << pokers[j].name << endl;
	cout << "Opponents: " << (k-1);
	cout << endl;
	int turns = chooseTypeOfCompetition(); //выбираем продолжительность соревнования

	Player *company[12];
	clearCompany();
	createCompany(company, k, name); // создаём пул игроков

	OneGame round;
	int currFirstPlayer = 0; //текущий первый игрок

	for (int i = 0; i < turns; i++)
	{
		int yourResult;
		try
		{
			yourResult = round.Go(company, k, pokers[j], turns, i, currFirstPlayer, name); //запускаем игровой тур
		}
		catch (...)
		{
			cout << "Sorry this round was interrupted" << endl;
			getch();
			yourResult = 0;
		}
		saveStatistic(pokers[j], yourResult, games, name, fileMistakes); //сохраняем статистику

		if (i + 1 < turns)
		{
			cout << "\nNext turn? (y/n)";
			char f = 'i';
			while (f != 'y' && f != 'n' && f != 'Y' && f != 'N')
			{
				f = getch();
			}
			if (f == 'n' || f == 'N')
			{
				cout << "\nExtremal stop\n";
				getch();
				break;
			}
			if (pokers[j].firstPlayerChanging == 1) //меняем сдающего, если это предусмотрено правилами
			{
				do
				{
					if (currFirstPlayer < k)
					{
						currFirstPlayer++;
					}
					if (currFirstPlayer == k)
					{
						currFirstPlayer = 0;
					}
				} while (company[currFirstPlayer]->inGame == -2);
			}
		} else
		{
			cout << "\n\nGame is end\n\n";
			int win = 0;
			int much = 0;
			for (int i = 0; i < k; i++)
			{
				if (company[i]->setMoney() == company[win]->setMoney())
				{
					much++;
				}
				if (company[i]->setMoney() > company[win]->setMoney())
				{
					much = 0;
					win = i;
				}
			}
			if (much == 0)
			{
				cout << "The winner is\n";
			} else
			{
				cout << "Winners are\n";
			}
			for (int i = 0; i < k; i++)
			{
				if (company[i]->setMoney() == company[win]->setMoney())
				{
					cout << company[i]->setName() << endl;
				}
			}
			if (yourResult==1)
				cout << "Congratulations!\n";
			getch();
		}

	}
}