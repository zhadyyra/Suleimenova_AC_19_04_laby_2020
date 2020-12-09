#pragma once
#include <iostream>
#include <fstream>
class Pipeline
{
private:
	int id;
	static int MaxId;
public:
	double length;
	int diameter;
	bool repear;
	int InputId;
	int OutputId;

	Pipeline();
	void EditPipeline();
	int GetId() const;

	friend std::ostream& operator << (std::ostream& out, const Pipeline& p);
	friend std::istream& operator >> (std::istream& in, Pipeline& p);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipeline& p);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipeline& p);
};
