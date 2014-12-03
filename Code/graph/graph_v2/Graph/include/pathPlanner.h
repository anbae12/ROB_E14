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

#include "robot.h"
#include "findPoints.h"
using namespace std;

class pathPlanner// : public cup_robot
{
    public:
      pathPlanner();
      //~pathPlanner();
        void addVertex(unsigned int topX, unsigned int topY, unsigned int bottomX, unsigned int bottomY);
        void getPath();
    
    typedef std::queue<coordinatesPair(int,int,int,int)> queue1;
    queue1 toJannik;
    
    
    struct coord {
        //coord(unsigned int x, unsigned int y) : x(x), y(y){};
        unsigned int x = 0, y = 0;
    };
    
    struct vertex {
        list<unsigned int> adj;
        unsigned int dist;
        std::vector<unsigned int> pathGrid;
        unsigned int identifier = 0;
        
        coord top, bottom;
        void setCoord(unsigned int topX, unsigned int topY, unsigned int bottomX, unsigned int bottomY) {
            top.x = topX;
            top.y = topY;
            bottom.x = bottomX;
            bottom.y = bottomY;
        }
        
        /*vertex() {
         for (unsigned int i = 0; i < 24; i++)
         pathGrid[i] = infinityCost;
         }*/
    };
    
    typedef vector<vertex> vertices_t;
    vertices_t vertices;
    
    list<unsigned int> path;
    
    
    private:
        const static unsigned int infinityCost = numeric_limits<unsigned int>::max();

    

        void createEdges();
        void createPathGrids();
        void generatePath();
};

#endif // PATHPLANNER_H
