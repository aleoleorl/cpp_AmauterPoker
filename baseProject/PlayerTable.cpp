#include "PlayerTable.h"

PlayerTable::PlayerTable()
{
	inGame = 0;
}

void PlayerTable::getCharas(int mn, string nm){}

void PlayerTable::showCards(int iAm, int currIs, int curPlayer, int nothingGood)
{
	if (onHand.size() > 0)
	{
		cout << "\ntable:\n";
		for (int i = 0; i < onHand.size(); i++)
		{
			if (onHand[i].viewIt == 0)
			{
				cout << "## ";
			}
			if (onHand[i].viewIt == 2)
			{
				showCard(onHand[i]);
			}
		}
	}
}