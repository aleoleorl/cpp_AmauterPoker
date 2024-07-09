#include "Player.h"

void Player::showCard(deck card)
{
	if (card.number < 9)
	{
		cout << card.number + 2;
	}
	else
	{
		if (card.number == 9)
		{
			cout << "V";
		}
		if (card.number == 10)
		{
			cout << "Q";
		}
		if (card.number == 11)
		{
			cout << "K";
		}
		if (card.number == 12)
		{
			cout << "A";
		}
	}
	if (card.suit == 0)
	{
		cout << (char)6; //����
	}
	if (card.suit == 1)
	{
		cout << (char)3; //�����
	}
	if (card.suit == 2)
	{
		cout << (char)4; //�����
	}
	if (card.suit == 3)
	{
		cout << (char)5; //�����
	}
	cout << " ";
}

Player::Player() {}

int Player::turn(Player *company[], int pl, rules gameRules, int round, int &curMaxBet, int currentFirstPlayer, int roundStartBet, int &bank, int myI) //������� ����
{//��� ������
	return 0;
}

void Player::turnB()
{ //��� ����� ����

}

void Player::changeCardInHand(deck card, int i) //������ ���������� ����� � ����
{
	onHand[i].number = card.number;
	onHand[i].suit = card.suit;
}

vector <deck> Player::getPrioritet(vector <deck> table, rules gameRules) //�������� ����������
{
	vector <deck> temp;
	return temp;
}

void Player::getCharas(int mn, string nm)
{}

void Player::clearHand() //������ ����
{
	while (onHand.size()>0)
	{
		onHand.pop_back();
	}
}

void Player::getOneCard(deck card) //����� ���� �����
{
	onHand.push_back(card);
}

vector <deck> Player::showHand() //�������� �����
{
	return onHand;
}

void Player::showCards(int iAm, int currIs, int curPlayer, int lenName)
{
	cout << "Yeh-yeh, I shown your cards\n";
}

void Player::clearBet()	{}

int Player::makeBet(int b)
{
	return 0;
}

string Player::setName()
{
	return "a";
}

int Player::setMoney()
{
	return 0;
}

void Player::getMoney(int n)
{
}

vector <int> Player::getCardToChange()
{ 
	vector <int> temp; 
	temp.push_back(0);
	return temp;
}

void Player::openCards() //������ ��� ����� ���������
{
	for (int i = 0; i<onHand.size(); i++)
	{
		if (onHand[i].viewIt == 0 || onHand[i].viewIt == 1)
		{
			onHand[i].viewIt = 2;
		}
	}
}