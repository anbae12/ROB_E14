//
//  findPoints.h
//
//  Created by Anders Launer Bæk on 29/09/14.
//
//

#ifndef _findPoints_h
#define _findPoints_h

#include "Image.hpp"
#include <queue>
struct coordinates{
    coordinates() : X(), Y(), Z() {}
    coordinates(double X, double Y, int Z)
    : X(X), Y(Y) , Z(Z) {}
    double X;
    double Y;
    int Z;
};

class findpoints{
    typedef std::queue<coordinates> queueOfPoints;
public:
    findpoints();
    void findP(rw::sensor::Image*, int, int const, int const);
//    queueOfPoints queue;
protected:
    int const freeSpace = 255;
    int const obstacleImage = 0;
    int const pointColor = 225;
private:
};

#endif /* defined(_findPoints_h) */