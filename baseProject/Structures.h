#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct deck
{
	int number;
	int suit;
	int viewIt=-1; //карта 2 - открыта для всех, 1 - только для игрока,
                    // 0 - закрыта для всех, -1 - не имеет значения
};

struct game //количество побед в определённой игре
{
	string name;//название игры
	int games;//сыграно игр
	int wins;//из них выиграно
	/*
	[name
	]gamename
	=games
	+wins
	]gamename
	=games
	+wins
	*/
};

struct player
{
	string name;
	int money;
};

struct oneTurn
{
	int cardsToPlayerOpen; //1
	int cardsToPlayerOpenForMe; //2
	int cardsToPlayerClose; //3
	int cardsOnTableOpen; //4
	int cardsOnTableClose; //5
	int cardsCanChangeOnHande; //6
};
struct rules
{
	string name; //n
	string rule; //r
	int maxPlayers; //1
	int tours; //раундов //2
	vector <oneTurn> turns; //ходов в раунде //t
	int chooseCardChanging; //можно ли менять карты с руки //3
	int bet; //базовая ставка //4
	int maxBet; //максимальная ставка //5
	int firstPlayerChanging; //меняется ли раздающий //6
	int startBet; // тип начальной ставки тура 0 - отсутствует 1 - первый игрок, 2 - (первый вносит половинную, второй полную), 3 - (второй вносит половинную, второй - полную),
										//9 - все //7
	int fromHand; //если показатель не равен 0, показывает, сколько карт игрок должен выбрать из руки как свою комбинацию
					//остальные карты добираются со стола //8
};

class Structures
{
};
