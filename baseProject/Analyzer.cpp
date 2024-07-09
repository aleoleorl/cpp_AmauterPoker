#include "Analyzer.h"

void Analyzer::f1(vector<N> &n, int curr, vector <deck> myDeck)
{
	for (int i = 0; i < myDeck.size(); i++) //����������� �� ���� ������ ������
	{
		int j = n[curr].structi.size(); //������� ���������� ���������������� ���� ��������������� �����
		
		if (myDeck[i].number == 1 + n[curr].structi[j - 1].number) //���� ���� ��������� ���������������� �����,
		{
			n.push_back(n[curr]); //��������� ��������� ����� � ��� ��������� �������������������
			//���� - ������ ����� ��������������� �����

			if (n[curr].structi.size() == 5) //��� ���� ���� ��������������� ������������������ ��� ����� 5 ����,
			{
				for (int k = 0; k < 4; k++) //����������� �� ������� �� ���
				{
					n[curr + 1].structi[k].number = n[curr + 1].structi[k + 1].number;
					n[curr + 1].structi[k].suit = n[curr + 1].structi[k + 1].suit;
				}
				n[curr + 1].structi.pop_back(); //������ ����� ��� ������ "����������"
			}

			dk preDk; //��������� ������������ �����
			preDk.cout = -1;
			preDk.number = myDeck[i].number;
			preDk.suit = myDeck[i].suit;
			n[n.size() - 1].structi.push_back(preDk);

			f1(n, n.size() - 1, myDeck); //��������, ���
		}
	}
}

double Analyzer::coefinator1(vector <deck> myDeck)
{
	//���� �� �����
	//vector <dk> combo1;
	combo1.erase(combo1.begin(), combo1.end());
	for (int i = 0; i < myDeck.size(); i++)
	{
		//cout << i << " = " << " (" << myDeck[i].number << "; " << myDeck[i].suit << " )" << endl;
		int j = 0;
		while (j < combo1.size())
		{
			if (myDeck[i].number == combo1[j].number)
			{
				combo1[j].cout++;
				break;
			}
			j++;
		}
		if (j == combo1.size())
		{
			dk one;
			one.cout = 1;
			one.number = myDeck[i].number;
			one.suit = myDeck[i].suit;
			combo1.push_back(one);
		}
	}
	//for (int i = 0; i < combo1.size(); i++)
	//	{
	//	cout << i << " = " << combo1[i].cout << " (" << combo1[i].number << "; " << combo1[i].suit << " )" << endl;
	//}
	//	cout << endl;

	//���� �� �����
	//vector <dk> combo2;
	combo2.erase(combo2.begin(), combo2.end());
	for (int i = 0; i < myDeck.size(); i++)
	{
		int j = 0;
		while (j < combo2.size())
		{
			if (myDeck[i].suit == combo2[j].suit)
			{
				combo2[j].cout++;
				if (myDeck[i].number>combo2[j].number) //��������� ������� ����� �����
				{
					combo2[j].number = myDeck[i].number;
				}
				break;
			}
			j++;
		}
		if (j == combo2.size())
		{
			dk one;
			one.cout = 1;
			one.number = myDeck[i].number;
			one.suit = myDeck[i].suit;
			combo2.push_back(one);
		}
	}

	//���� ������������������
	//vector <N> combo3;
	combo3.erase(combo3.begin(), combo3.end());
	for (int i = 0; i < myDeck.size(); i++)
	{
		dk dk3;
		dk3.number = myDeck[i].number;
		dk3.suit = myDeck[i].suit;
		N N3;
		N3.structi.push_back(dk3);
		combo3.push_back(N3);
		f1(combo3, combo3.size() - 1, myDeck);
	}
	int i = 0;

	while (i < combo3.size()) //������ ����� - ����������� �� �������������������, ������� 5-� ����
	{
		if (combo3[i].structi.size() < 5)
		{
			combo3.erase(combo3.begin() + i);
			i--;
		}
		i++;
	}
	/*for (int i = 0; i < combo3.size(); i++)
	{
	for (int j = 0; j < combo3[i].structi.size(); j++)
	{
		cout << i << " = " << combo3[i].structi[j].cout << " (" << combo3[i].structi[j].number << "; " << combo3[i].structi[j].suit << " )" << endl;
	}
	cout << endl;*/

	return 0;
}

double Analyzer::coefinator2()
{
	//��������� �����
	double high3 = 0;
	int coutSt = 0;
	int numSt = 0;
	for (int i = 0; i < combo3.size(); i++)
	{
		high3 = 5;
		if (combo3[i].structi[4].number>coutSt) //� ��� ����� 5 ���� �� ��������
		{
			coutSt = combo3[i].structi[4].number;
			numSt = i;
		}
	}
	if (high3 != 0)
	{
		high3 += (double)coutSt / 100;
	}

	//��������� ����
	double high2 = 0;
	int coutHi = 0;
	int numHi = 0;
	for (int i = 0; i < combo2.size(); i++)
	{
		if (combo2[i].cout >= 5)
		{
			high2 = 6;
			if (coutHi < combo2[i].number) //������� ����� �����
			{
				coutHi = combo2[i].number;
				numHi = i;
			}
		}
	}
	if (high2 != 0)
	{
		high2 += (double)combo2[numHi].number / 100;
	}

	//��������� ������������� ������
	if (high3 >= 5 && high2 >= 6)
	{
		int suitSF = -1; //����� ������������������
		int numSF = 0; //����� ������������������
		int coutSF = 0; //���������� ���� ������������������
		for (int i = 0; i < combo3.size(); i++) //�������� �� ���� ��������� �������������������
		{
			if ((coutSF == 0) || (coutSF != 0 && combo3[i].structi[4].number>combo3[numSF].structi[4].number))
			{ //���� ��� ��� ������ ������������������, ���� ������ ����� ����� ������������������ �������
				int suitsf = -1; //����� ������������������
				int numsf = 0; //����� ������������������
				int coutsf = 0; //���������� ���� ������������������
				for (int j = 0; j < 5; j++) //�������� �� ���� 5 ������ ��������������� ������������������
				{
					if (suitsf == -1 || combo3[i].structi[j].suit == suitsf)
					{ //���� ��� ������ �����, ���� ����� ���������
						numsf = i;
						coutsf++;
						suitsf = combo3[i].structi[j].suit;
					}
					else //� ����� ������ ���� �� �����? �������
					{
						break;
					}
				}
				if (coutsf == 5)
				{
					suitSF = suitsf;
					numSF = numsf;
					coutSF = coutsf;
				}
			}
		}
		if (coutSF != 0) //���� ���������� ����!!!
		{
			if (combo3[numSF].structi[4].number == 12)
			{
				high3 = 10;
			}
			else
			{
				high3 = 9;
			}
			high3 += (double)combo3[numSF].structi[4].number / 100;
		}
	}

	// ������ ��������� ������������������ ���������� ����
	int cout1 = 0;
	int num1 = 0;
	for (int i = 0; i < combo1.size(); i++)
	{
		if (combo1[i].cout>cout1)
		{
			cout1 = combo1[i].cout;
			num1 = i;
		}
		if (combo1[i].cout == cout1 && combo1[i].number > combo1[num1].number)
		{
			cout1 = combo1[i].cout;
			num1 = i;
		}
	}

	// ������ ��������� ������������������ ���������� ����
	int cout2 = 0;
	int num2 = 0;
	for (int i = 0; i < combo1.size(); i++)
	{
		if (combo1[i].cout>cout2 && i != num1)
		{
			cout2 = combo1[i].cout;
			num2 = i;
		}
		if (combo1[i].cout == cout2  && i != num1 && combo1[i].number > combo1[num2].number)
		{
			cout2 = combo1[i].cout;
			num2 = i;
		}
	}

	double high = 0;

	if (cout1 == 4)
	{ //����
		high = 8;
		high += ((double)combo1[num1].number / 100);
	}
	if (cout2 == 4)
	{ //����
		high = 8;
		high += ((double)combo2[num2].number / 100);
	}

	if (high <8 && cout1 == 3 && cout2 == 3)
	{ //������ ���
		high = 7;
		if (combo1[num1].number > combo2[num2].number)
		{
			high += ((double)combo1[num1].number / 100);
		}
		else
		{
			high += ((double)combo1[num1].number / 100);
		}
	}
	if (high <8 && ((cout1 == 2 && cout2 == 3) || (cout1 == 3 && cout2 == 2)))
	{ //������ ���
		high = 7;
		if (cout1 == 3)
		{
			high += ((double)combo1[num1].number / 100);
		}
		else
		{
			high += ((double)combo1[num1].number / 100);
		}
	}

	if (high <4 && ((cout1 == 3 && cout2 <3) || (cout1 <3 && cout2 == 3)))
	{ //������
		high = 4;
		if (cout1 == 3)
		{
			high += ((double)combo1[num1].number / 100);
		}
		else
		{
			high += ((double)combo1[num1].number / 100);
		}
	}

	if (high <4 && (cout1 == 2 && cout2 == 2))
	{ //��� ����
		high = 3;
		if (combo1[num1].number> combo1[num2].number)
		{
			high += ((double)combo1[num1].number / 100);
		}
		else
		{
			high += ((double)combo1[num1].number / 100);
		}
	}

	if (high <3 && cout1 == 2)
	{ //����
		high = 2;
		high += ((double)combo1[num1].number / 100);
	}

	if (high <2 && cout1 == 1)
	{ //������� �����
		high = 1;
		high += ((double)combo1[num1].number / 100);
	}

	if (high3>high2 && high3 > high)
	{
		return high3;
	}
	if (high2>high3 && high2 > high)
	{
		return high2;
	}
	if (high>high2 && high > high3)
	{
		return high;
	}

	return 0;
}

Analyzer::Analyzer() {}

double Analyzer::getPrioritet(vector <deck> hero, vector <deck> table)
{
	vector <deck> myDeck;
	for (int i = 0; i < hero.size(); i++)
	{
		if (hero[i].viewIt == 1 || hero[i].viewIt == 2)
		{
			myDeck.push_back(hero[i]);
		}
	}	
	if (myDeck.size() != 0) //��������� �� ������, ���� ����� �������
	{
		for (int i = 0; i < table.size(); i++)
		{
			if (table[i].viewIt == 1 || table[i].viewIt == 2)
			{
				myDeck.push_back(table[i]);
			}
		}
	}
	else { return 0; }
	
	coefinator1(myDeck); //������ ����� ������� - ������������ �� ������������������ ��������� ����������
	
	return coefinator2(); //������ ����� ������� - �������� ���������� ������������������
}