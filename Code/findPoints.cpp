//
//  findPoints.cpp
//
//  Created by Anders Launer Bæk on 29/09/14.
//
//

#include <iostream>
#include "findPoints.h"

void findpoints::findP(rw::sensor::Image* img, int channel, int const imageWidth, int const imageHeight){
    // loop vertical through picture
    for (double j=1; j<imageWidth-1; j++) {
        for (double k=1; k<imageHeight-1; k++) {
            // 1
            if (img->getPixelValuei( j, k, channel ) == freeSpace &&
                img->getPixelValuei( j, k-1, channel ) == obstacleImage &&
                img->getPixelValuei( j-1, k, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,1));
            }
            // 2
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k-1, channel ) == obstacleImage &&
                    img->getPixelValuei( j+1, k, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,2));
            }
            // 3
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == obstacleImage &&
                    img->getPixelValuei( j-1, k, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,3));
            }
            // 4
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == obstacleImage &&
                    img->getPixelValuei( j+1, k, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,4));
            }
            // 5
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k-1, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,5));
            }
            // 6
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k-1, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,6));
            }
            // 7
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k+1, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,5));
            }
            // 8
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j+1, k+1, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k-1, channel ) == freeSpace &&
                    img->getPixelValuei( j-1, k+1, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,6));
            }
        }
    }
}