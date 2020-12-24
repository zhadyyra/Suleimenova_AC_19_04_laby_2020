#include "Pipeline.h"
#include "Utils.h"
#include <limits>
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
	Weight = 0;
	Throughput = 0;
}
void Pipeline::EditPipeline()
{
	repear = !repear;
}
int Pipeline::GetId() const
{
	return id;
}
int Pipeline::GetWeight() const
{
	return (int)length;
}
int Pipeline::GetThroughput() const
{
	return (int)sqrt(pow(diameter, 5) / length);
}
ostream& operator << (ostream& out, const Pipeline& p)
{
	cout << "\nID: " << p.id
		<< "\tДлина: " << p.length
		<< "\tДиаметр: " << p.diameter
		<< "\tВ ремонте: " << (p.repear ? "В ремонте" : "Не в ремонте") 
		<< "\tВВод ID: " << p.InputId
		<< "\tВывод ID: " << p.OutputId
		<< "\tВес: " << p.Weight
		<< "\tПропускная способность:" << p.Throughput << endl;
	return out;
}
istream& operator >> (istream& in, Pipeline& p)
{
	p.length = GetCorrectNumber(0.0, DBL_MAX, "ВВедите длину:");
	p.diameter = GetCorrectNumber(0, INT_MAX, "ВВедите диаметр:");
	p.repear = false;
	p.Weight = p.GetWeight();
	p.Throughput = p.GetThroughput();
	return in;
}

ofstream& operator<<(ofstream& fout, const Pipeline& p)
{
	fout << p.id << endl << p.length << endl << p.diameter << endl << p.repear << endl << p.InputId << endl << p.OutputId << p.Weight << p.Throughput<< endl;
	return fout;
}
ifstream& operator>>(std::ifstream& fin, Pipeline& p)
{
	fin >> p.id >> p.length >> p.diameter >> p.repear >> p.InputId >> p.OutputId >> p.Weight >> p.Throughput;
	return fin;
}
