//
//  findPoints.cpp
//
//  Created by Anders Launer Bæk on 29/09/14.
//
//

#include <iostream>


#include "findPoints.h"

void findpoints::findPone(rw::sensor::Image* img){
    // loop vertical through picture
    for (double j=1; j<img->getWidth()-1; j++) {
        for (double k=1; k<img->getHeight()-1; k++) {
            // 1
            if (img->getPixelValuei( j, k, channel ) == freeSpace &&
                img->getPixelValuei( j, k-1, channel ) == obstacleImage &&
                img->getPixelValuei( j-1, k, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,1));
                img->setPixel8U(j,k,pointColor);
            }
            // 2
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k-1, channel ) == obstacleImage &&
                    img->getPixelValuei( j+1, k, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,2));
                img->setPixel8U(j,k,pointColor);
            }
            // 3
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == obstacleImage &&
                    img->getPixelValuei( j-1, k, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,3));
                img->setPixel8U(j,k,pointColor);
            }
            // 4
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == obstacleImage &&
                    img->getPixelValuei( j+1, k, channel ) == obstacleImage) {
                queue.push(coordinates(j,k,4));
                img->setPixel8U(j,k,pointColor);
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
                img->setPixel8U(j,k,pointColor);
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
                img->setPixel8U(j,k,pointColor);
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
                queue.push(coordinates(j,k,7));
                img->setPixel8U(j,k,pointColor);
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
                queue.push(coordinates(j,k,8));
                img->setPixel8U(j,k,pointColor);
            }
        }
    }
}

void findpoints::findPtwo(rw::sensor::Image* img){
    // loop vertical through picture
    for (double j=1; j<img->getWidth()-1; j++) {
        for (double k=1; k<img->getHeight()-1; k++) {
            // 1
            if (img->getPixelValuei( j, k, channel ) == freeSpace &&
                img->getPixelValuei( j, k-1, channel ) == rectangularColor &&
                img->getPixelValuei( j-1, k, channel ) == rectangularColor) {
                queue.push(coordinates(j,k,1));
                img->setPixel8U(j,k,pointColor);
            }
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == rectangularColor &&
                    img->getPixelValuei( j-1, k, channel ) == rectangularColor) {
                queue.push(coordinates(j,k,3));
                img->setPixel8U(j,k,pointColor);
            }
            // 4
            else if(img->getPixelValuei( j, k, channel ) == freeSpace &&
                    img->getPixelValuei( j, k+1, channel ) == rectangularColor &&
                    img->getPixelValuei( j+1, k, channel ) == rectangularColor) {
                queue.push(coordinates(j,k,4));
                img->setPixel8U(j,k,pointColor);
            }
        }
    }
}

void findpoints::stageOne(rw::sensor::Image* img){
    while (!queue.empty()) {
        j=queue.front().X;
        k=queue.front().Y;
        
        int tempJ=j;
        int tempK=k;
        bool state=true;
        while (state) {
            ++tempK;
            if (img->getPixelValuei(tempJ, tempK, channel) == obstacleImage) {
                state=false;
                --tempK;
            }
            
            if (img->getPixelValuei(tempJ, tempK, channel) == pointColor) {
                state=false;
                --tempK;
            }
            img->setPixel8U(tempJ , tempK , rectangularColor);
        }
        state=true;
        tempJ=j;
        tempK=k;
        while (state) {
            --tempK;
            if (img->getPixelValuei(tempJ, tempK, channel) == obstacleImage) {
                state=false;
                ++tempK;
            }
            
            if (img->getPixelValuei(tempJ, tempK, channel) == pointColor) {
                state=false;
                ++tempK;
            }
            img->setPixel8U(tempJ , tempK , rectangularColor);
        }
        state=true;
        tempJ=j;
        tempK=k;
        while (state) {
            ++tempJ;
            if (img->getPixelValuei(tempJ, tempK, channel) == obstacleImage) {
                state=false;
                --tempJ;
            }
            
            if (img->getPixelValuei(tempJ, tempK, channel) == pointColor) {
                state=false;
                --tempJ;
            }
            img->setPixel8U(tempJ , tempK , rectangularColor);
        }
        state=true;
        tempJ=j;
        tempK=k;
        while (state) {
            --tempJ;
            if (img->getPixelValuei(tempJ, tempK, channel) == obstacleImage) {
                state=false;
                ++tempJ;
            }
            
            if (img->getPixelValuei(tempJ, tempK, channel) == pointColor) {
                state=false;
                ++tempJ;
            }
            img->setPixel8U(tempJ , tempK , rectangularColor);
        }
        
        img->setPixel8U(queue.front().X , queue.front().Y , pointColor);
        queue.pop();
    }
}

void findpoints::stageTwo(rw::sensor::Image* img){
    while (!queue.empty()) {
        double J=queue.front().X;
        double K=queue.front().Y;
        double tempJ=queue.front().X;
        double tempK=queue.front().Y;
        
        if (queue.front().Z==1){
            if (img->getPixelValuei(tempJ, tempK, channel) == pointColor) {
                
            }else{
                do ++tempK;
                while (img->getPixelValuei(tempJ, tempK, channel) != pointColor);
            }
            
            if (img->getPixelValuei(tempJ, tempK, channel) == pointColor) {
                
            }else{
                do ++tempJ;
                while (img->getPixelValuei(tempJ, tempK, channel) != pointColor);
            }
            queuePair.push_back(coordinatesPair(J-1,K-1,tempJ+1,tempK+1));
            queue.pop();
            queue.pop();
        }else
            queue.pop();
    }
}

void findpoints::printPair(){
    while (!queuePair.empty()) {
    
        std::cout<<queuePair.back().X<<","<<queuePair.back().Y<<" ; "<<queuePair.back().Xx<<","<<queuePair.back().Yy<<std::endl;
    queuePair.pop_back();
    }
}

void findpoints::preparePicture(rw::sensor::Image* img){
    for (int i=0; i<img->getWidth(); i++) {
        img->setPixel8U(i , 0 , obstacleImage);
        img->setPixel8U(i , img->getHeight()-1 , obstacleImage);
    }
    for (int i=0; i<img->getHeight(); i++) {
        img->setPixel8U(0 , i , obstacleImage);
        img->setPixel8U(img->getWidth()-1,i , obstacleImage);
    }
}

void findpoints::findDiagonals(rw::sensor::Image* img, int chan){
    channel=chan;
    preparePicture(img);
    findPone(img);
    stageOne(img);
    findPtwo(img);
    stageTwo(img);
    printPair();
    
}

