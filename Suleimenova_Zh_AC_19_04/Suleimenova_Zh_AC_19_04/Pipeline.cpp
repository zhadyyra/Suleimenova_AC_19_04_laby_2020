#include "Pipeline.h"
#include "Utils.h"
using namespace std;

int Pipeline::MaxId = 0;
Pipeline::Pipeline()
{
	id = ++MaxId;
	length = 0.0;
	diameter = 0;
	repear = false;
	InputId = 0;
	OutputId = 0;
}
void Pipeline::EditPipeline()
{
	repear = !repear;
}
int Pipeline::GetId() const
{
	return id;
}
ostream& operator << (ostream& out, const Pipeline& p)
{
	cout << "\niD: " << p.id
		<< "\tДлина: " << p.length
		<< "\tДиаметр: " << p.diameter
		<< "\tРемонт: " << (p.repear ? "В ремонте" : "Не в ремонте") << endl;
	return out;
}
istream& operator >> (istream& in, Pipeline& p)
{
	p.length = GetCorrectNumber(0.0, DBL_MAX, "Введите длину:");
	p.diameter = GetCorrectNumber(0, INT_MAX, "Введите диаметр:");
	p.repear = false;
	return in;
}

ofstream& operator<<(ofstream& fout, const Pipeline& p)
{
	fout << p.id << endl << p.length << endl << p.diameter << endl << p.repear << endl;
	return fout;
}
ifstream& operator>>(std::ifstream& fin, Pipeline& p)
{
	fin >> p.id >> p.length >> p.diameter >> p.repear;
	return fin;
}
