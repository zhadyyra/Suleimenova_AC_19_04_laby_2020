#include "Ks.h"
#include "Utils.h"
#include <limits>
using namespace std;

int Ks::MaxId = 0;
Ks::Ks()
{
	id = ++MaxId;
	name = "��� ��������";
	ceh = 0;
	cehwork = 0;
	effective = 0.0;
}
void Ks::EditKs(int LaunchCeh)
{
	if (LaunchCeh && cehwork < ceh) cehwork++;
	if (!LaunchCeh && cehwork) cehwork--;
}
int Ks::GetId() const
{
	return id;
}
ostream& operator<<(ostream& out, const Ks& k)
{
	cout << "\nID: " << k.id
		<< "\t��������: " << k.name
		<< "\t���������� �����: " << k.ceh
		<< "\t���������� ����� � ������: " << k.cehwork
		<< "\t�������������: " << k.effective;
	return out;
}

istream& operator>>(istream& in, Ks& k)
{
	cout << "������� ��������:";
	cin.ignore(1, '\n');
	getline(cin, k.name);
	k.ceh = GetCorrectNumber(0, INT_MAX, "������� ��:");
	k.cehwork = GetCorrectNumber(0, INT_MAX, "������� �� � ������:");
	k.effective = GetCorrectNumber(0.0, DBL_MAX, "������� �������������:");
	return in;
}

ofstream& operator<<(ofstream& fout, const Ks& k)
{
	fout << k.id << endl << k.name << endl << k.ceh << endl << k.cehwork << endl << k.effective << endl;
	return fout;
}

ifstream& operator>>(ifstream& fin, Ks& k)
{
	fin >> k.id;
	fin.ignore(1, '\n');
	getline(fin, k.name);
	fin >> k.ceh >> k.cehwork >> k.effective;
	return fin;
}
