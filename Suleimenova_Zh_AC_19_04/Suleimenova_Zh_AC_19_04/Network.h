#pragma once
#include "Pipeline.h"
#include "Ks.h"
#include <unordered_map>
#include <map>
#include <set>
#include <stack>
#include <queue>
using namespace std;

class Network
{
private:
	unordered_map <int, int> mGtsKs;
	unordered_map <int, Pipeline> mGtsPipe;
	map < pair<int, int>, int > network;
	map < pair<int, int>, int > throughputs;
	void DFS(int start, vector<int>& color, stack <int>& temp);
	int FindVertex(string str);
	int BFS(int stvertex, int endvertex, vector <int>& way, map <pair<int, int>, int>& flow);
	void FindWay(int vertex, stack <int>& way, const vector <int>& distance);
	void PrintTable(map<pair<int, int>, int>& table);

	bool cycle_found;

public:
	set <int> GtsPipe;
	set <int> GtsKs;
	bool NetworkExist;

	Network();
	void CreateConnection(unordered_map<int, Pipeline>& Pipeline_s, const unordered_map<int, Ks>& Ks_s);
	void CreateNetwork(const unordered_map<int, Pipeline>& Pipeline_s);
	void KsDelChanges(int id, unordered_map <int, Pipeline>& Pipeline_s);
	void PipeDelChanges(int id);
	void PrintNetwork();
	void SaveNetwork(const unordered_map<int, Pipeline>& Pipeline_s, const unordered_map<int, Ks>& Ks_s);
	void LoadNetwork(unordered_map<int, Pipeline>& Pipeline_s, unordered_map<int, Ks>& Ks_s);
	void TopolSort(const unordered_map<int, Pipeline>& Pipeline_s);
	void ShortDist();
	void MaxFlow();
};
