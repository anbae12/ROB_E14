//
//  BrushFireAlgorithm.h
//  Brushfire
//
//  Created by Anders Launer Bæk on 29/09/14.
//
//

#ifndef __Brushfire__BrushFireAlgorithm__
#define __Brushfire__BrushFireAlgorithm__

#include "Image.hpp"

class brushFireAlgorithm{
public:
    bool compare(double, double);
    void BrushFireAlgorithm(rw::sensor::Image*, int, int const, int const);

protected:
    int freeSpace = 255;
    int robotPathMoved = 125;
    int obstacleImage = 0;
    int obstacleBrushFire = 1;
    int untouchedByFire = -1;
    double lastBrushFireNumber = 1;
    bool whileState;
    
    
    
    int stopstop = 10;

private:
};

#endif /* defined(__Brushfire__BrushFireAlgorithm__) */
