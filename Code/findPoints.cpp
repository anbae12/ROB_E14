//
//  BrushFireAlgorithm.cpp
//  Brushfire
//
//  Created by Anders Launer Bæk on 29/09/14.
//
//

#include "BrushFireAlgorithm.h"


#include <iostream>

bool brushFireAlgorithm::compare(double d,double c){
    bool state;
    if (d-c==0)
        state = true;
    if (d-c!=0)
        state = false;
    return state;
}




void brushFireAlgorithm::BrushFireAlgorithm(rw::sensor::Image* img, int channel,int const pW, int const pH){
    double brushFireValue[pW][pH];
    // plotting obstacles and free space
    for (int i=0; i<pW; i++) {
        for (int j=0; j<pH; j++) {
            if (img->getPixelValuei( i, j, channel ) == obstacleImage)
                 brushFireValue[i][j] = obstacleBrushFire;
            if (img->getPixelValuei( i, j, channel ) == freeSpace)
                brushFireValue[i][j] = untouchedByFire;
        }
    }
    std::cout<<"plotting obstacles done..."<<std::endl;
    whileState = true;
    
    while ( whileState==true ){
        lastBrushFireNumber++;
        for (int i=1; i<pW-1; i++) {
            for (int j=1; j<pH-1; j++) {
                if (compare(brushFireValue[i][j],(lastBrushFireNumber-1))==true) {
                    if (compare(brushFireValue[i-1][j], untouchedByFire) == true){ brushFireValue[i-1][j] = lastBrushFireNumber; }
                    if (compare(brushFireValue[i][j+1], untouchedByFire) == true){ brushFireValue[i][j+1] = lastBrushFireNumber; }
                    if (compare(brushFireValue[i+1][j], untouchedByFire) == true){ brushFireValue[i+1][j] = lastBrushFireNumber; }
                    if (compare(brushFireValue[i][j-1], untouchedByFire) == true){ brushFireValue[i][j-1] = lastBrushFireNumber; }
                    // Checking if start position is overwritten and then set whileState = false.
                    if (compare(brushFireValue[i-1][j], lastBrushFireNumber) == true){ brushFireValue[i-1][j] = lastBrushFireNumber; whileState = false;}
                    if (compare(brushFireValue[i][j+1], lastBrushFireNumber) == true){ brushFireValue[i][j+1] = lastBrushFireNumber; whileState = false;}
                    if (compare(brushFireValue[i+1][j], lastBrushFireNumber) == true){ brushFireValue[i+1][j] = lastBrushFireNumber; whileState = false;}
                    if (compare(brushFireValue[i][j-1], lastBrushFireNumber) == true){ brushFireValue[i][j-1] = lastBrushFireNumber; whileState = false;}
                }
            }
        }
        if (lastBrushFireNumber == 5) {
            whileState = false;
        }
        
    }
}
