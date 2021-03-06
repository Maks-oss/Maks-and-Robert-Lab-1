﻿#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

void readf(string filename, string country[20], int vvv[20][20], int &kk);
void countscore(int ctry, int vvv[20][20], int k, int score[20]);
void top10sort(string country[20], int score[20], int k);
void topout(string country[20], int score[20], int k);

int main()
{
	int kk = 0;
	int vvv[20][20];
	int score[20] = { 0 };
	string country[20];

	WIN32_FIND_DATAA findData;
	HANDLE hfind;
	string p;
	setlocale(0, "ukrainian");
	cout << "Введiть шлях до папки з вхiдними файлами: ";
	cin >> p;
	p += "\\*.csv";
	
	hfind = FindFirstFileA(p.c_str(), &findData);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		cout << "Cannot find file" << endl;
		return -1;
	}
	do
	{
		string rrr = findData.cFileName;
		readf(("D:\\Euro\\"+rrr), country, vvv, kk);
		//cout << findData.cFileName << endl;
		//cout << rrr << endl;
	}
	while (FindNextFileA(hfind, &findData));

	FindClose(hfind);

	for (int i = 0; i < 20; i++) countscore(i, vvv, kk, score);
	top10sort(country, score, kk);
	topout(country, score, kk);
	return 0;
}

void topout(string country[20], int score[20], int k)
{
	string ff;
	cout << "Введiть шлях до папки для збереження результату: ";
	cin >> ff;
	ff += "\\results.csv";
	ofstream fout(ff);
	for (int i = 0; i < (k > 10 ? 10 : k); i++)
	{
		if (country[i].find('\n') == 0) country[i].erase(0, 1);
		fout << country[i] << "," << score[i] << endl;
	}
	fout.close();
}
void top10sort(string country[20], int score[20], int k)
{
	int h;
	string hh;
	for (int i = 0; i < k - 1; i++)
	{
		for (int j = i+1; j < k; j++)
		{
			if (score[i] < score[j])
			{
				hh = country[i];
				country[i] = country[j];
				country[j] = hh;
				h = score[i];
				score[i] = score[j];
				score[j] = h;
			}
		}
	}
}
void countscore(int ctry, int vvv[20][20], int k, int score[20])
{
	int nv[20][2];
	int h;
	for (int i = 0; i < k; i++)
	{
		nv[i][0] = vvv[i][ctry];
		nv[i][1] = i;
	}
	for (int i = 0; i < k-1; i++)
	{
		for (int j = i; j < k; j++)
		{
			if (nv[i][0] < nv[j][0])
			{
				h = nv[i][0];
				nv[i][0] = nv[j][0];
				nv[j][0] = h;
				h = nv[i][1];
				nv[i][1] = nv[j][1];
				nv[j][1] = h;
			}
		}
	}
	for (int i = 0; i < (k > 10 ? 10 : k); i++)
	{
		if (i == 0) score[nv[i][1]] += 12;
		else if (i == 1) score[nv[i][1]] += 10;
		else if (i >= 2 && i <= 10) score[nv[i][1]] += 10 - i;
	}
}
void readf(string filename, string country[20], int vvv[20][20], int &kk)
{
	ifstream fin(filename);
	string LINE;
	string add;
	int c = -1;
	fin >> c;
	for (int i = 0+kk; i < c+kk; i++)
	{
		getline(fin, country[i], ',');
		for (int j = 0; j < 19; j++)
		{
			getline(fin, LINE, ',');
			vvv[i][j] = stoi(LINE);
		}
		getline(fin, LINE, '\n');
		vvv[i][19] = stoi(LINE);
	}
	kk += c;
	fin.close();
}