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
#include "wavefront.h"


struct coordinates{
    coordinates() : x(), y(), z() {}
    coordinates(int x, int y, int z) : x(x), y(y) , z(z) {}
    int x;
    int y;
    int z;
};

struct coordinatesPair{
    coordinatesPair() : x(), y(), Xx(), Yy() {}
    coordinatesPair(int x, int y, int Xx, int Yy)
    : x(x), y(y), Xx(Xx), Yy(Yy) {}
    int x, Xx;
    int y, Yy;
};


class findpoints: public wavefront{
private:
    int const freeSpace = 255;
    int const obstacleImage = 0;
    int const pointColor = 225;
    int const rectangularColor = 111;
    int tempJ, tempK, j, k;
    int channel;
    
    findpoints();
    void findPone(rw::sensor::Image*);
    void findPtwo(rw::sensor::Image*);
    void preparePicture(rw::sensor::Image*);
    void stageOne(rw::sensor::Image*);
    void stageTwo(rw::sensor::Image*);
    void printPair();
    
    typedef std::queue<coordinates> queueOfPoints;
    queueOfPoints queue;
    
public:
    findpoints(Image *img);

    void findDiagonals(rw::sensor::Image*, int);
    typedef std::vector<coordinatesPair> queueOfPoints2;
    queueOfPoints2 queuePair;
    
    
protected:
};

#endif /* defined(_findPoints_h) */