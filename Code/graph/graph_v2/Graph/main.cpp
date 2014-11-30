#include <iostream>
#include <vector>

#include "pathPlanner.h"


using namespace std;

int main (){
    struct paul {
        paul(unsigned int X, unsigned int Y, unsigned int Xx, unsigned int Yy) : X(X), Xx(Xx), Y(Y), Yy(Yy){};
        unsigned int X = 0, Xx = 0, Y = 0, Yy = 0;
    };
    pathPlanner test;

    vector<paul> grete;
    grete.push_back(paul(5, 5, 14, 50));
    grete.push_back(paul(16, 5, 26, 50));
    grete.push_back(paul(28, 5, 37, 50));
    grete.push_back(paul(16, 52, 26, 54));
    grete.push_back(paul(5, 56, 14, 94));
    grete.push_back(paul(16, 56, 26, 94));
    grete.push_back(paul(28, 56, 41, 94));
    grete.push_back(paul(43, 56, 65, 94));
    grete.push_back(paul(43, 45, 65, 54));
    grete.push_back(paul(43, 36, 65, 43));
    grete.push_back(paul(67, 45, 69, 54));
    grete.push_back(paul(71, 45, 75, 54));
    grete.push_back(paul(77, 45, 87, 54));
    grete.push_back(paul(89, 45, 94, 54));
    grete.push_back(paul(71, 56, 75, 94));
    grete.push_back(paul(77, 56, 87, 94));
    grete.push_back(paul(89, 56, 94, 94));
    grete.push_back(paul(71, 36, 75, 43));
    grete.push_back(paul(77, 36, 87, 43));
    grete.push_back(paul(89, 36, 94, 43));
    grete.push_back(paul(77, 32, 87, 34));
    grete.push_back(paul(89, 5, 94, 30));
    grete.push_back(paul(77, 5, 87, 30));
    grete.push_back(paul(43, 5, 75, 30));

    for (vector<paul>::iterator vertex = grete.begin(); vertex != grete.end(); vertex++) {
        test.addVertex(vertex->X, vertex->Y, vertex->Xx, vertex->Yy);
    }

    test.getPath();
    return 0;
}
