#include "PokerCoordinator.h"

void PokerCoordinator::makeName()
{
	games.erase(games.begin(), games.end()); //не забываем подчищать статистику после других игроков

	int n = 0;
	while (n == 0)
	{
		system("cls");
		cout << "Amauter Poker Application\n\n";

		cout << "Input your name:\n>";
		name = "";
		do
		{
			getline(cin, name);
		} while (name == "");
		if (name.size() > 100) //обрезаем длину имени
		{
			name.resize(100);
		}

		char* s = new char[100];
		strcpy(s, name.c_str());
		strcat(s, ".app.txt");

		FILE*f = fopen(s, "rb");
		if (f != 0)
		{
			cout << "This name already exists. Are you sure to delete old save? (y/n)\n";
			char c = 'l';
			while (c != 'y' && c != 'n' && c != 'Y' && c != 'N')
			{
				c = getch();
			}
			if (c == 'y' || c=='Y')
			{
				if (fclose(f) != 0)
				{
					cout << "Sorry. Your statistics may be not correct working this time\n"; 
					fileMistakes++;
					getch();
				}
				else
				{
					f = fopen(s, "wb");
					if (f) // если есть доступ к файлу
					{
						string temp = "]" + name;
						bool result = fputs(temp.c_str(), f); // и записываем ее в файл
						if (result)
						{
							cout << "Sorry. Your statistics may be not correct working this time\n";
							fileMistakes++;
							getch();
						}
						fclose(f);
					}
					else
					{
						cout << "Sorry. Your statistics may be not correct working this time\n";
						fileMistakes++;
						getch();
					}					
				}
				n = 1;
			}
			if (c == 'n' || c=='N')
			{
				if (fclose(f) != 0)
				{
					cout << "Sorry. Your statistics may be not correct working this time\n";
					fileMistakes++;
					getch();
				}
			}
		}
		else
		{
			f = fopen(s, "wb");
			if (f) // если есть доступ к файлу
			{
				string temp = "]" + name;
				bool result = fputs(temp.c_str(), f); // и записываем ее в файл
				if (result)
				{
					cout << "Sorry. Your statistics may be not correct working this time\n";
					fileMistakes++;
					getch();
				}
			}
			else
			{
				cout << "Sorry. Your statistics may be not correct working this time\n";
				fileMistakes++;
				getch();
			}
			fclose(f);

			n = 1; //выходим из цикла
		}
	}
}

void PokerCoordinator::showStatistic() //показываем статистику игрока
{
	system("cls");
	cout << "Amauter Poker Application\n\n";

	cout << "Results of " << name << " games:\n\n";
	if (games.size() == 0)
	{
		cout << "You havn't play yet.\n";
	}
	else
	{
		for (int i = 0; i < games.size(); i++)
		{
			cout << "\"" << games[i].name << "\":" << endl;
			cout << "(wins/games) " << games[i].wins << "/" << games[i].games << endl;
			cout << endl;
		}
	}
	getch();
}

void PokerCoordinator::readStatistic(string name) //считываем из файла
{
	ifstream f;
	char mystring[10000];
	string v;

	char* s = new char[100];
	strcpy(s, name.c_str());
	strcat(s, ".app.txt");

	f.open(s, ios::binary | ios::in);
	if (!f.is_open())
	{
		cout << "Sorry. Your statistics may be not correct working this time\n";
		fileMistakes++;
		getch();
	}
	else
	{		
		f.getline(mystring, 10000);

		if (mystring[0] != EOF)
		{
			int i = 0;

			string gameName = ""; //название игры
			int gameNums;
			int gameWins;

			while (i<10000)
			{
				if (mystring[i] == '[') //готовимся принять имя новой игры
				{
					gameName = "";
					i++;					
					do
					{
						gameName += mystring[i];
						i++;
					} while (mystring[i] != '=');
				}

				if (mystring[i] == '=') //принимаем число сыгранный игр (определённой игры)
				{
					i++;
					gameNums = 0;
					int temp = 0;
					do
					{
						temp = mystring[i];
						temp -= 48;
						gameNums = gameNums * 10 + temp;
						i++;
					} while (mystring[i] != '+');
				}
				if (mystring[i] == '+') //принимаем число побед (определённой игры)
				{
					i++;
					gameWins = 0;
					int temp;
					do
					{
						temp = mystring[i] - 48;
						gameWins = gameWins * 10 + temp;
						i++;
					} while (mystring[i] != ']');
				}
				if (mystring[i] == ']') //формируем игры в вектор статистики
				{
					if (gameName != "")
					{
						game n;
						n.name = gameName;
						n.games = gameNums;;
						n.wins = gameWins;;
						games.push_back(n);
					}
				}
				i++;
			}
		}
		f.close();
	}
}

int PokerCoordinator::loadName()
{
	system("cls");
	cout << "Amauter Poker Application\n\n";

	char path[70] = ""; //путь к папке
	char mask[15] = "*app.txt"; //маска файла

	strcat(path, mask);

	_finddata_t *fileinfo = new _finddata_t; //указателя fileinfo на структуру _finddata_t и создание динамического объекта структуры _finddata_t

	long done = _findfirst(path, fileinfo); //ищем первый файл
	int mayWeWork = done; // если done будет равняться -1, то поиск вести бесмысленно

	int count = 0;// Счетчик, содержит информацию о количестве найденых файлов.
	vector <string> s;
	while (mayWeWork != -1)
	{
		count++;
		s.push_back(fileinfo->name);
		s[s.size() - 1].resize(s[s.size() - 1].size() - 8);
		cout << (s.size()) << " - " << s[s.size() - 1] << endl;

		mayWeWork = _findnext(done, fileinfo); //ищем следующий файл
	}

	_findclose(done); //закрываемся
	delete fileinfo; //и чистимся

	if (s.size() == 0) //файлов не обнаружено
	{
		cout << "There are no players for now. Please create new one.\n";
		getch();
		return 1;
	}

	cout << "Choose your player (1-" << (s.size()) << "):\n> "; //если игроки обнаружены
	int num = -1;
	while (num<1 || num>s.size())
	{
		cin >> num;
	}
	name = s[num - 1]; //имя - выбрано

	readStatistic(name); //считаем статистику из файла

	return 0;
}

void PokerCoordinator::about()
{
	system("cls");
	cout << "Amauter Poker Application\n\n";
	cout << "developed by Alex Orlovsky for ITStep\n";
	cout << "2014\n";
}

int PokerCoordinator::startMenu()
{
	system("cls");
	cout << "Amauter Poker Application\n\n";

	cout << "1 - create new player\n\n3 - load your player\n\n9 - out";
	fileMistakes = 0;
	char g = 'l';
	while (g != '1' && g != '3' && g != '9')
	{
		g = getch();
	}
	if (g == '1')
	{
		makeName();
		return 0;
	}
	if (g == '3')
	{
		return loadName();
	}
	if (g == '9')
	{
		about();
		return 9;
	}
	return 9;
}

int PokerCoordinator::menu(Tournament tour)
{
	int n = 0;

	system("cls");

	cout << "Amauter Poker Application\n\n";
	cout << "1 - play\n\n5 - show statistic\n\n7 - change player\n\n9 - out\n";
	char c = 'l';
	while (c != '1' && c != '5' && c != '7' && c != '9')
	{
		cout << "(?)";
		c = getch();
	}
	if (c == '1')
	{
		system("cls");
		cout << "Amauter Poker Application\n\n";
		tour.tour(pokers, name, games, fileMistakes);
	}
	if (c == '5')
	{
		showStatistic();
	}
	if (c == '7')
	{
		games.erase(games.begin(), games.end());  //чистим статистику
		startMenu();
	}
	if (c == '9')
	{
		about();
		n = 1;
	}

	return n;
}

PokerCoordinator::PokerCoordinator()
{
	srand(time(0));
	fileMistakes = 0;
	setlocale(LC_ALL, "Russian");
}

void PokerCoordinator::go()
{
	int e = 1;
	while (e == 1)
	{
		e = startMenu();
	}

	if (e == 0)
	{
		RulesMaker rm;
		rm.manager(pokers);

		Tournament tour;

		int n = 0;
		do
		{
			n = menu(tour);
		} while (n == 0);
	}
}