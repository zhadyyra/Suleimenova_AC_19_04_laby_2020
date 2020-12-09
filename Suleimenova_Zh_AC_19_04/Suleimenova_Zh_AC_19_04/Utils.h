#pragma once     //Proverka
#include <iostream>
#include <string>
template <typename T>
T GetCorrectNumber(T min, T max, std::string Message)
{
	T vvod;
	std::cout << Message;
	while ((std::cin >> vvod).fail() || (vvod < min) || (vvod > max))
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << Message;
	}
	return vvod;
}
