#include "graph.h"

graph::graph()
{

}
graph::~graph()
{

}

void graph::loadFile(string filename)
{
	string data1, data2;
	fstream file;
	file.open(filename);

	while (getline(file, data1)){
		data2 = data1.substr(data1.find(';') + 1);
		data1 = data1.erase(data1.find(';'), data1.length());

		//adjacencyList.emplace(coordSet(stoi(data1.substr(data1.find(',') - 1)), stoi(data1.substr(data1.find(',') + 1)), stoi(data2.substr(data1.find(',') - 1)), stoi(data2.substr(data1.find(',') + 1))),neighbors);
		adjacencyList[coordSet(5, 5, 14, 50)] = neighbors;
	}
	//cout << adjacencyList.begin()->first.x1 << endl;
}