#pragma once
#include "Pipeline.h"
#include "Ks.h"
#include <unordered_map>
#include <set>
using namespace std;

class Network
{
public:
	set <int> GtsPipe;
	set <int> GtsKs;
	bool NetworkExist;

	Network();
};
