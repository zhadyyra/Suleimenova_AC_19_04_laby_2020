#pragma once
#include <string>
#include <fstream>
class Ks
{
private:
	int id;
	static int MaxId;

public:
	std::string name;
	int ceh;
	int cehwork;
	double effective;

	Ks();
	void EditKs(int LaunchCeh);
	int GetId() const;

	friend std::ostream& operator << (std::ostream& out, const Ks& k);
	friend std::istream& operator >> (std::istream& in, Ks& k);
	friend std::ofstream& operator << (std::ofstream& fout, const Ks& k);
	friend std::ifstream& operator >> (std::ifstream& fin, Ks& k);
};
