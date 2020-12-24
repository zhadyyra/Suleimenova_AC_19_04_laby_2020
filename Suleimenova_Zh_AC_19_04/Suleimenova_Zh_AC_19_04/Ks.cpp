#include "Ks.h"
#include "Utils.h"
#include <limits>
using namespace std;

int Ks::MaxId = 0;
Ks::Ks()
{
	id = ++MaxId;
	name = "Нет названия";
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
		<< "\tНазвание: " << k.name
		<< "\tКоличество цехов: " << k.ceh
		<< "\tКоличество цехов в работе: " << k.cehwork
		<< "\tЭффективность: " << k.effective;
	return out;
}

istream& operator>>(istream& in, Ks& k)
{
	cout << "Введите название:";
	cin.ignore(1, '\n');
	getline(cin, k.name);
	k.ceh = GetCorrectNumber(0, INT_MAX, "ВВедите КЦ:");
	k.cehwork = GetCorrectNumber(0, INT_MAX, "ВВедите КЦ в работе:");
	k.effective = GetCorrectNumber(0.0, DBL_MAX, "ВВедите эффективность:");
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
