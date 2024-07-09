#include "RulesMaker.h"

RulesMaker::RulesMaker()
{
}

rules RulesMaker::ramRule()
{
	rules poker;
	poker.name = "Double Discarding Draw-poker";
	poker.bet = 100;
	poker.maxBet = 500;
	poker.rule = "–азновидность дро-покера, в котором игроки производ€т две замены карт за кон.\n";
	poker.rule += "»гроки внос€т начальную ставку и получают п€ть карт закрытыми.\nƒалее следует круг торговли.\n";
	poker.rule += "»гроки объ€вл€ют, что они мен€ют несколько карт.—дающий забирает их карты и сдаЄт им столько же новых.\n";
	poker.rule += "ƒалее следует круг торговли.\n»гроки второй раз объ€вл€ют, что они мен€ют несколько карт.—дающий забирает их карты и сдаЄт им столько же новых.\n";
	poker.rule += "—ледует последний круг торговли.\nќдновременно может играть до семи игроков.";
	poker.maxPlayers = 7;
	poker.tours = 1;
	poker.chooseCardChanging = 1;
	poker.firstPlayerChanging = 1;
	poker.startBet = 1;
	poker.fromHand = 0;

	oneTurn oT;
	oT.cardsToPlayerOpen = 0;
	oT.cardsToPlayerOpenForMe = 5;
	oT.cardsToPlayerClose = 0;
	oT.cardsOnTableOpen = 0;
	oT.cardsOnTableClose = 0;
	oT.cardsCanChangeOnHande = 5;
	poker.turns.push_back(oT);
	oT.cardsToPlayerOpen = 0;
	oT.cardsToPlayerOpenForMe = 0;
	oT.cardsToPlayerClose = 0;
	oT.cardsOnTableOpen = 0;
	oT.cardsOnTableClose = 0;
	oT.cardsCanChangeOnHande = 5;
	poker.turns.push_back(oT);
	oT.cardsToPlayerOpen = 0;
	oT.cardsToPlayerOpenForMe = 0;
	oT.cardsToPlayerClose = 0;
	oT.cardsOnTableOpen = 0;
	oT.cardsOnTableClose = 0;
	oT.cardsCanChangeOnHande = 0;
	poker.turns.push_back(oT);

	return poker;
}

int RulesMaker::loading(vector <rules> &pokers)
{
	//открытие файла на чтение
	FILE*f = fopen("rules.txt", "r");
	if (!f) return 1;

	rules poker; //правила дл€ покера
	oneTurn oT; //правила дл€ тура
	char c; //переменна€ дл€ считывани€ файла
	string command = ""; //условна€ команда поведени€ со считанным символом
	
	do {
		c = fgetc(f);
		//cout << c;

		if (c == '*')
		{
			//cout << "*" << endl;
			//getch();
			if (poker.name.size() != 0)
			{
				command = "";
				poker.name.resize(poker.name.size() - 1);
				poker.rule[poker.rule.size() - 1] = '\0';
				//cout << poker.name << endl;
				//cout << poker.rule << endl;
				//cout << poker.turns.size() << endl;
				//getch();
				if (poker.turns.size() != 0)
				{
					poker.bet = 100;
					poker.maxBet = 500;
					poker.tours = 1;
					pokers.push_back(poker);
				}
			}
			poker.name = "";
			poker.bet = 0;
			poker.maxBet = 0;
			poker.rule = "";
			poker.maxPlayers = 0;
			poker.tours = 0;
			poker.chooseCardChanging = 0;
			poker.firstPlayerChanging = 0;
			poker.fromHand = 0;
			poker.startBet = 0;
			poker.turns.erase(poker.turns.begin(), poker.turns.end());
			continue;
		}

		if (c == ']')
		{
			command = "]";
			if (c != EOF)
			{
				c = fgetc(f);
			}
			else { return 2; }
			command += c;
			if (c != EOF)
			{
				c = fgetc(f);
			}
			else { return 2; }

			if (command == "]1")
			{
				poker.maxPlayers = c - 48;
				//cout << "poker.maxPlayers=" << poker.maxPlayers<<endl;
				command = "";
			}
			if (command == "]3")
			{
				poker.chooseCardChanging = c - 48;
				command = "";
			}
			if (command == "]6")
			{
				poker.firstPlayerChanging = c - 48;
				command = "";
			}
			if (command == "]7")
			{
				poker.startBet = c - 48;
				command = "";
			}
			if (command == "]8")
			{
				poker.fromHand = c - 48;
				command = "";
			}
			
			if (command == "]t") //начало формировани€ правил раунда
			{
				oT.cardsToPlayerOpen = 0;
				oT.cardsToPlayerOpenForMe = 0;
				oT.cardsToPlayerClose = 0;
				oT.cardsOnTableOpen = 0;
				oT.cardsOnTableClose = 0;
				oT.cardsCanChangeOnHande = 0;
				command = "";
			}
			if (command == "]0") //конец формировани€ правил раунда
			{
				poker.turns.push_back(oT);
				command = "";
			}
		}

		if (command == "]n" && c != ']') //название игры
		{			
			poker.name += c;
		}		
		if (command == "]r" && c != ']') //правила игры
		{
			//cout << poker.rule;
			poker.rule += c;
		}

		if (c == '[')
		{
			command = "[";
			if (c != EOF)
			{
				c = fgetc(f);
			} else { return 2; }
			command += c;

			if (c != EOF)
			{
				c = fgetc(f);
			} else { return 2; }

			if (command == "[1")
			{
				oT.cardsToPlayerOpen = c - 48;
			}
			if (command == "[2")
			{
				oT.cardsToPlayerOpenForMe = c - 48;
			}
			if (command == "[3")
			{
				oT.cardsToPlayerClose = c - 48;
			}
			if (command == "[4")
			{
				oT.cardsOnTableOpen = c - 48;
			}
			if (command == "[5")
			{
				oT.cardsOnTableClose = c - 48;
			}
			if (command == "[6")
			{
				oT.cardsCanChangeOnHande = c - 48;
			}
			command = "";
		}
	} while (c != EOF);

	pokers.push_back(ramRule());

	fclose(f);

	//getch();
	return 0;
}

void RulesMaker::manager(vector <rules> &pokers)
{
	int i;
	try
	{
		i = loading(pokers);
		if (i != 0)
		{
			throw i;
		}
	}
	catch (int i)
	{
		system("cls");
		if (i == 1)
		{
			cout << "Couldn't open file with rules\n";
		}
		if (i == 2)
		{
			cout << "File with rules was corrupted\n";
		}
		pokers.push_back(ramRule());
		if (pokers.size() == 1)
		{
			cout << "Sorry! Could be use only one type of the game.\n";
		}
		getch();
	}
}