#ifndef PATHPLANNER_H
#define PATHPLANNER_H

#include <utility>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <queue>
#include <limits>
#include <list>

using namespace std;

class pathPlanner
{
    public:
        pathPlanner();
        ~pathPlanner();
        void addVertex(unsigned int topX, unsigned int topY, unsigned int bottomX, unsigned int bottomY);
        void getPath();
    private:
        unsigned int infinityCost = numeric_limits<unsigned int>::max();
        struct coord {
            //coord(unsigned int x, unsigned int y) : x(x), y(y){};
            unsigned int x = 0, y = 0;
        };

        struct vertex {
            list<unsigned int> adj;
            unsigned int dist;
            unsigned int path;

            coord top, bottom;
            void setCoord(unsigned int topX, unsigned int topY, unsigned int bottomX, unsigned int bottomY) {
                top.x = topX;
                top.y = topY;
                bottom.x = bottomX;
                bottom.y = bottomY;
            }
        };

        typedef vector<vertex> vertices_t;
        vertices_t vertices;

        queue<unsigned int> path;

        void createEdges();
        void generatePath();
};

#endif // PATHPLANNER_H
