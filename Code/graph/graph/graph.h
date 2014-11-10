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
		bool operator==(const coordSet &other){
			//Compare coords of two sets.
		}
		coordSet(int x1, int y1, int x2, int y2) :x1(x1), y1(y1), x2(x2), y2(y2) {};
		unsigned int x1, y1, x2, y2;
	};
	void loadFile(string);
	void loadData(vector<coordSet>);
private:
	typedef unsigned int cost_t;
	typedef coordSet vertex_t;
	typedef vector <pair<vertex_t, cost_t>> neighbors_t; 
	typedef map<vertex_t, neighbors_t> adjacencyList_t;
	adjacencyList_t adjacencyList;
	neighbors_t neighbors;
};

