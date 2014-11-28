#include "graph.h"

graph::graph()
{

}
graph::~graph()
{

}

void graph::createEdges(){
	neighbors_t neighbors;

	for (adjacencyList_t::iterator vertex = adjacencyList.begin(); vertex != adjacencyList.end(); vertex++)
	{
		//Check top
		if (adjacencyList.find(coordSet(vertex->first.x1, vertex->first.y1, vertex->first.x2, vertex->first.y2)) != adjacencyList.end())
			cout << "test" << endl;
	}
}

void graph::loadFile(string filename)
{
	string data1, data2;
	fstream file;
	file.open(filename);

	while (getline(file, data1)){
		data2 = data1.substr(data1.find(';') + 1);
		data1 = data1.erase(data1.find(';'), data1.length());

		adjacencyList.emplace(coordSet(stoi(data1.substr(0, data1.find(',') + 1)), stoi(data1.substr(data1.find(',') + 1)), stoi(data2.substr(0, data2.find(',') + 1)), stoi(data2.substr(data2.find(',') + 1))), neighbors);
	}

	createEdges();
}