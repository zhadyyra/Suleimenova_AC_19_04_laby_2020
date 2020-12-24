#pragma once
#include <iostream>
#include <string>
using namespace std;

template <typename T>
T GetCorrectNumber(T min, T max, string Message)
{
	T vvod;
	cout << Message;
	while ((cin >> vvod).fail() || (vvod < min) || (vvod > max))
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << Message;
	}
	return vvod;
}
inline string AskingForName()
{
	string filename;
	cout << "\nPlease, enter the name: ";
	cin.ignore(1, '\n');
	getline(cin, filename);
	return filename;
}
