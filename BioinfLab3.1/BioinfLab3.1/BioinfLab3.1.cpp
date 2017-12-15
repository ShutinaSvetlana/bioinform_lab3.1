#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include"algorithm"
using namespace std;


pair<int*, int> ByPass(int* a, int i, int l, int k)
{
	for (int j = i; j > -1; j--)
	{
		if (a[j] < k-1)
		{	
			a[j]++;
			return make_pair(a,j);
		}
	}
	return make_pair(a,-1);
}

pair<int*, int>  NextVertex(int* a, int i, int l, int k)
{
	if (i < l)
	{
		a[i + 1] = 0;
		return make_pair(a, i+1);
	}
	else
	{
		for (int j = l-1; j > -1; j--)
		{
			if (a[j] < k-1)
			{
				a[j]++;
				return make_pair(a,j);
			}
		}
	}
	return make_pair(a,-1);
}

int Score(int* s, string* str, int i, int l)
{
	int score = 0;
	int* count = new int[4];
	for (int i = 0; i < 4; i++)
		count[i] = 0;
	int* countAll = new int[l];
	for (int k = 0; k < l; k++)
	{
		for (int u = 0; u < 4; u++)
			count[u] = 0;
		for (int j = 0; j < i; j++)
		{
			if (str[j].c_str()[s[j] + k] == 'A')
				count[0]++;
			else
			{
				if (str[j].c_str()[s[j] + k] == 'C')
					count[1]++;
				else
				{
					if (str[j].c_str()[s[j] + k] == 'G')
						count[2]++;
					else
						count[3]++;
				}
			}
		}
		countAll[k] = max(max(max(count[0], count[1]), count[2]), count[3]);
		score += countAll[k];
	}	
	return score;
}

string* BestMotif(int* s, string* str, int t, int l)
{
	string* result = new string[t];
	for (int i = 0; i < t; i++)
		result[i] = str[i].substr(s[i], l);
	return result;
}


string* SearchMotif(string* str, int t, int l)
{
	int n = strlen(str[0].c_str());
	int* s = new int[t];
	int* bestS = new int[t];
	for (int i = 0; i < t; i++)
		s[i] = 0;
	int bestScore = 0;
	int optimisticScore = 0;
	int i = 0;
	string* bestMotifs = new string[t];	
	pair<int*, int> p;
	while (i > -1)
	{
		if (i < t-1)
		{
			optimisticScore = Score(s, str, i+1, l) + (t - i-1)*l;
			if (optimisticScore < bestScore)
			{
				p = ByPass(s, i, t, n - l+1);
				s = p.first;
				i = p.second;
			}
			else
			{				
				p = NextVertex(s, i, t, n - l+1);
				s = p.first;
				i = p.second;
			}
		}
		else
		{
			if (Score(s, str, t, l) >= bestScore)
			{
				bestScore = Score(s, str, t, l);
				for (int j = 0; j < t; j++)
					bestS[j] = s[j];
				bestMotifs = BestMotif(bestS, str, t, l);
			}
			p = NextVertex(s, i, t, n - l + 1);
			s = p.first;
			i = p.second;
		}
	}	
	return bestMotifs;
}



int main()
{
	setlocale(LC_ALL, ".1251");

	ifstream input("input.txt"); // ������� ���� ��� ������	
	string l1; //������ �������
	input >> l1; //������� ���-��	

	int l; //������ �������
	l = atoi(l1.c_str()); //������� � int	

	string t1; //���-�� �����
	input >> t1; //������� ���-��	

	int t; //���-�� �����	
	t = atoi(t1.c_str()); //������� � int	

	string* str = new string[t]; //������
	getline(input, str[0]); //������� ������ ������ �� ����� �� �����
	for (int i = 0; i < t; i++)
		getline(input, str[i]); //������� ������ �� �����

	string* result = new string[t]; //���������
	result = SearchMotif(str, t, l); //����� 

	input.close(); // ��������� ����

	ofstream output; //������� ���� ��� ������
	output.open("output.txt"); //������� ���� ��� ������	
	for (int i = 0; i < t; i++)
		output << result[i] << endl;
	output.close(); // ��������� ����

	delete[] str;
	delete[] result;

	return 0;
}

