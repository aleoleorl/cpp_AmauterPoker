#include "Deck.h"

void Deck::showDeck(vector <deck> curDeck)
{
	int i = 0;
	for (vector<deck>::iterator it = curDeck.begin(); it != curDeck.end(); ++it)
	{
		cout << i++ << ": ";
		if (it->number < 9)
		{
			cout << it->number + 2;
		}
		else
		{
			if (it->number == 9)
			{
				cout << "J";
			}
			if (it->number == 10)
			{
				cout << "Q";
			}
			if (it->number == 11)
			{
				cout << "K";
			}
			if (it->number == 12)
			{
				cout << "A";
			}
		}
		if (it->suit == 0)
		{
			cout << (char)6; //����
		}
		if (it->suit == 1)
		{
			cout << (char)3; //�����
		}
		if (it->suit == 2)
		{
			cout << (char)4; //�����
		}
		if (it->suit == 3)
		{
			cout << (char)5; //�����
		}
		cout << endl;
	}	
}

Deck::Deck()
{
	deck a;
	a.viewIt = 0;
	for (int i = 0; i < 4; i++)
	{
		//2,3,4,5,6,7,8,9,10,j,q,k,a
		for (int j = 0; j < 13; j++)
		{
			a.number = j;
			a.suit = i;
			defaultDeck.push_back(a);
		}
	}
}

vector <deck> Deck::Stir() //������������ �����
{
	gameDeck.erase(gameDeck.begin(), gameDeck.end());

	vector <deck> tempDeck = defaultDeck; //���� ������ ������, ��� � ������� ("defaultDeck")

	while (tempDeck.size() > 0)
	{
		int i = rand() % tempDeck.size();
		deck temp;
		temp = tempDeck[i];
		gameDeck.push_back(temp);
		tempDeck.erase(tempDeck.begin() + i);
	}
	return gameDeck;
}

deck Deck::getOneCard()
{
	deck temp;
	if (gameDeck.size() == 0)
	{
		Stir(); //��������� ��������� ������
	}

	temp = gameDeck[gameDeck.size() - 1];
	gameDeck.pop_back();

	return temp;
}