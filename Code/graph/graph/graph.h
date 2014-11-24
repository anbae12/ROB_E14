#pragma once
#include "vector"
#include "map"
#include "fstream"
#include "string"
#include "iostream"

using namespace std;

class graph
{
public:
	graph();
	~graph();

	struct coordSet{
		coordSet(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) :x1(x1), y1(y1), x2(x2), y2(y2) {};
		unsigned int x1, y1, x2, y2;
	};

	struct compare_coordSet
	{
		inline bool operator() (const coordSet& first, const coordSet& second) const
		{
			return first.x1 == second.x1 ? first.y1 < second.y1 : first.x1 < second.x1;
		}
	};

	void loadFile(string);
	void loadData(vector<coordSet>);
	void createEdges();
private:
	typedef unsigned int cost_t;
	typedef coordSet vertex_t;
	typedef vector <pair<vertex_t, cost_t>> neighbors_t; 
	typedef map<vertex_t, neighbors_t, compare_coordSet> adjacencyList_t;
	adjacencyList_t adjacencyList;
};

