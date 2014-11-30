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
        const static unsigned int infinityCost = numeric_limits<unsigned int>::max();

        struct coord {
            //coord(unsigned int x, unsigned int y) : x(x), y(y){};
            unsigned int x = 0, y = 0;
        };

        struct vertex {
            list<unsigned int> adj;
            unsigned int dist;
            unsigned int pathGrid[24];
            unsigned int identifier = 0;

            coord top, bottom;
            void setCoord(unsigned int topX, unsigned int topY, unsigned int bottomX, unsigned int bottomY) {
                top.x = topX;
                top.y = topY;
                bottom.x = bottomX;
                bottom.y = bottomY;
            }

            vertex() {
                for (unsigned int i = 0; i < 24; i++)
                    pathGrid[i] = infinityCost;
            }
        };

        typedef vector<vertex> vertices_t;
        vertices_t vertices;

        list<unsigned int> path;

        void createEdges();
        void createPathGrids();
        void generatePath();
};

#endif // PATHPLANNER_H
