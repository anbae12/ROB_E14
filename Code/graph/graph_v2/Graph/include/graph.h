#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <queue>

using namespace std;

class graph
{
    public:
        graph();
        ~graph();
        void addVertex(unsigned int topX, unsigned int topY, unsigned int bottomX, unsigned int bottomY);
        void createEdges();
        void routePlanning();
        void printEdges();
    private:
        struct coord {
            coord(unsigned int x, unsigned int y) : x(x), y(y){};
            unsigned int x = 0, y = 0;
        };

        struct edge {
            edge (unsigned int src, unsigned int dest, unsigned int cost) : src(src), dest(dest), cost(cost){};
            unsigned int src = 0, dest = 0, cost = 0;

            bool operator < (const edge& rhs) const {
                return cost < rhs.cost;
            }
        };

        typedef pair<coord, coord>  vertex_t;
        typedef vector<vertex_t>    vertices_t;
        typedef vector<edge>        edges_t;

        vertices_t vertices;
        edges_t edges;
};

#endif // GRAPH_H
