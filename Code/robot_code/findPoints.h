//
//  findPoints.h
//
//  Created by Anders Launer Bæk on 29/09/14.
//
//

#ifndef _findPoints_h
#define _findPoints_h

#include "Image.hpp"
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>



struct coordinates{
    coordinates() : X(), Y(), Z() {}
    coordinates(double X, double Y, int Z)
    : X(X), Y(Y) , Z(Z) {}
    double X;
    double Y;
    int Z;
};

struct coordinatesPair{
    coordinatesPair() : X(), Y(), Xx(), Yy() {}
    coordinatesPair(double X, double Y, double Xx, double Yy)
    : X(X), Y(Y), Xx(Xx), Yy(Yy) {}
    double X, Xx;
    double Y, Yy;
};


class findpoints{
    
    typedef std::queue<coordinates> queueOfPoints;
    typedef std::vector<coordinatesPair> queueOfPoints2;
    
    
public:
    findpoints();
    void findPone(rw::sensor::Image*);
    void findPtwo(rw::sensor::Image*);
    void preparePicture(rw::sensor::Image*);
    void stageOne(rw::sensor::Image*);
    void stageTwo(rw::sensor::Image*);
    void printPair();
    void findDiagonals(rw::sensor::Image*, int);
    queueOfPoints queue;
    queueOfPoints2 queuePair;
protected:
    int const freeSpace = 255;
    int const obstacleImage = 0;
    int const pointColor = 225;
    int const rectangularColor = 111;
    int tempJ, tempK, j, k;
    int channel;

private:
};

#endif /* defined(_findPoints_h) */