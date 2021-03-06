//
//  findPoints.cpp
//
//  Created by Anders Launer Bæk on 29/09/14.
//
//

#include <iostream>


#include "findPoints.h"

findpoints::findpoints(Image *img): wavefront(img){
    map=img;
}

void findpoints::createArray(){
    array3D.resize(map->getWidth());
    for (int i = 0; i < map->getWidth(); ++i) {
        array3D[i].resize(map->getHeight());
    }
    
    for (int j=0; j<map->getWidth(); j++) {
        for (int k=0; k<map->getHeight(); k++) {
            array3D[j][k]=map->getPixelValuei(j, k, channel);
        }
    }
    
    array3D[62][51]=freeSpace;
    array3D[63][51]=freeSpace;
    array3D[64][51]=freeSpace;
    array3D[65][51]=freeSpace;
    array3D[66][51]=freeSpace;
    array3D[67][51]=freeSpace;
    array3D[68][51]=freeSpace;
    array3D[69][51]=freeSpace;
    array3D[70][51]=freeSpace;
    array3D[71][51]=freeSpace;
    array3D[72][51]=freeSpace;
    array3D[73][51]=freeSpace;
    array3D[74][51]=freeSpace;
    
}

void findpoints::findPone(){
    // loop vertical through picture
    
    for (int j=1; j<map->getWidth()-1; j++) {
        for (int k=1; k<map->getHeight()-1; k++) {
            if (wavefront_mask[k][j]>=2) {
                // 1
                if (array3D[j][k] == freeSpace &&
                    array3D[j][k-1] == obstacleImage &&
                    array3D[j-1][k] == obstacleImage) {
                    queue.push(coordinates(j,k,1));
                    array3D[j][k]=pointColor;
                }
                // 2
                else if(array3D[j][k] == freeSpace &&
                        array3D[j][k-1] == obstacleImage &&
                        array3D[j+1][k] == obstacleImage) {
                    queue.push(coordinates(j,k,2));
                    array3D[j][k]=pointColor;
                }
                // 3
                else if(array3D[j][k] == freeSpace &&
                        array3D[j][k+1] == obstacleImage &&
                        array3D[j-1][k] == obstacleImage) {
                    queue.push(coordinates(j,k,3));
                    array3D[j][k]=pointColor;
                }
                // 4
                else if(array3D[j][k] == freeSpace &&
                        array3D[j][k+1] == obstacleImage &&
                        array3D[j+1][k] == obstacleImage) {
                    queue.push(coordinates(j,k,4));
                    array3D[j][k]=pointColor;
                }
                // 5
                else if(array3D[j][k] == freeSpace &&
                        array3D[j][k-1] == freeSpace &&
                        array3D[j][k+1] == freeSpace &&
                        array3D[j+1][k] == freeSpace &&
                        array3D[j-1][k] == freeSpace &&
                        array3D[j-1][k-1] == freeSpace &&
                        array3D[j-1][k+1] == freeSpace &&
                        array3D[j+1][k+1] == freeSpace &&
                        array3D[j+1][k-1] == obstacleImage) {
                    queue.push(coordinates(j,k,5));
                    array3D[j][k]=pointColor;
                }
                // 6
                else if(array3D[j][k] == freeSpace &&
                        array3D[j][k-1] == freeSpace &&
                        array3D[j][k+1] == freeSpace &&
                        array3D[j+1][k] == freeSpace &&
                        array3D[j-1][k] == freeSpace &&
                        array3D[j+1][k-1] == freeSpace &&
                        array3D[j+1][k+1] == freeSpace &&
                        array3D[j-1][k+1] == freeSpace &&
                        array3D[j-1][k-1] == obstacleImage) {
                    queue.push(coordinates(j,k,6));
                    array3D[j][k]=pointColor;
                }
                // 7
                else if(array3D[j][k] == freeSpace &&
                        //array3D[j][k-1] == freeSpace &&
                        array3D[j][k+1] == freeSpace &&
                        array3D[j+1][k] == freeSpace &&
                        array3D[j-1][k] == freeSpace &&
                        array3D[j-1][k-1] == freeSpace &&
                        array3D[j-1][k+1] == freeSpace &&
                        array3D[j+1][k-1] == freeSpace &&
                        array3D[j+1][k+1] == obstacleImage) {
                    queue.push(coordinates(j,k,7));
                    array3D[j][k]=pointColor;
                }
                // 8
                else if(array3D[j][k] == freeSpace &&
                        //array3D[j][k-1] == freeSpace &&
                        array3D[j][k+1] == freeSpace &&
                        array3D[j+1][k] == freeSpace &&
                        array3D[j-1][k] == freeSpace &&
                        array3D[j+1][k-1] == freeSpace &&
                        array3D[j+1][k+1] == freeSpace &&
                        array3D[j-1][k-1] == freeSpace &&
                        array3D[j-1][k+1] == obstacleImage) {
                    queue.push(coordinates(j,k,8));
                    array3D[j][k]=pointColor;
                }
            }
            
        }
    }
}
void findpoints::stageOne(){
    while (!queue.empty()) {
        j=queue.front().x;
        k=queue.front().y;
        
        int tempJ=j;
        int tempK=k;
        bool state=true;
        while (state) {
            ++tempK;
            if (array3D[tempJ][tempK] == obstacleImage) {
                state=false;
                --tempK;
            }
            
            if (array3D[tempJ][tempK] == pointColor) {
                state=false;
                --tempK;
            }
            array3D[tempJ][tempK]=rectangularColor;
        }
        state=true;
        tempJ=j;
        tempK=k;
        while (state) {
            --tempK;
            if (array3D[tempJ][tempK] == obstacleImage) {
                state=false;
                ++tempK;
            }
            
            if (array3D[tempJ][tempK] == pointColor) {
                state=false;
                ++tempK;
            }
            array3D[tempJ][tempK]=rectangularColor;
        }
        state=true;
        tempJ=j;
        tempK=k;
        while (state) {
            ++tempJ;
            if (array3D[tempJ][tempK] == obstacleImage) {
                state=false;
                --tempJ;
            }
            
            if (array3D[tempJ][tempK] == pointColor) {
                state=false;
                --tempJ;
            }
            array3D[tempJ][tempK]=rectangularColor;
        }
        state=true;
        tempJ=j;
        tempK=k;
        while (state) {
            --tempJ;
            if (array3D[tempJ][tempK] == obstacleImage) {
                state=false;
                ++tempJ;
            }
            
            if (array3D[tempJ][tempK] == pointColor) {
                state=false;
                ++tempJ;
            }
            array3D[tempJ][tempK]=rectangularColor;
        }
        
        map->setPixel8U(queue.front().x , queue.front().y , pointColor);
        queue.pop();
    }
}
void findpoints::findPtwo(){
    // loop vertical through picture
    for (int j=1; j<map->getWidth()-1; j++) {
        for (int k=1; k<map->getHeight()-1; k++) {
            
            
            if (wavefront_mask[k][j]>=2) {
                // 1
                if (array3D[j][k] == freeSpace &&
                    array3D[j][k-1] == rectangularColor &&
                    array3D[j-1][k] == rectangularColor &&
                    //array3D[j-1][k-1] == rectangularColor &&
                    array3D[j+1][k] == freeSpace &&
                    array3D[j+1][k+1] == freeSpace) {
                    queue.push(coordinates(j,k,1));
                    array3D[j][k]=pointColor;
                }
                
                // 9 left
                else if(array3D[j][k] == freeSpace &&
                        array3D[j+1][k] == freeSpace &&
                        array3D[j-1][k] == rectangularColor &&
                        array3D[j][k+1] == rectangularColor &&
                        array3D[j][k-1] == rectangularColor) {
                    queue.push(coordinates(j,k,2));
                    //array3D[j][k]=obstacleImage;
                }
                
                
                // 10 bottom
                else if(array3D[j][k] == freeSpace &&
                        array3D[j-1][k] == rectangularColor &&
                        array3D[j+1][k] == rectangularColor &&
                        array3D[j][k-1] == rectangularColor &&
                        array3D[j][k+1] == freeSpace) {
                    queue.push(coordinates(j,k,3));
                    // array3D[j][k]=obstacleImage;
                }
                
                // 11 center
                if(array3D[j][k] == freeSpace &&
                   array3D[j-1][k] == rectangularColor &&
                   array3D[j+1][k] == rectangularColor &&
                   
                   array3D[j][k-1] == rectangularColor &&
                   array3D[j][k+1] == rectangularColor &&
                   
                   array3D[j-1][k-1] == rectangularColor &&
                   array3D[j+1][k+1] == rectangularColor &&
                   
                   array3D[j-1][k+1] == rectangularColor &&
                   array3D[j+1][k+1] == rectangularColor) {
                    queue.push(coordinates(j,k,4));
                    //array3D[j][k]=obstacleImage;
                    std::cout<<"center"<<std::endl;
                }
                
            }
        }
    }
}



void findpoints::stageTwo(){
    while (!queue.empty()) {
        int J=queue.front().x;
        int K=queue.front().y;
        int tempJ=queue.front().x;
        int tempK=queue.front().y;
        
        if (queue.front().z==1) {
            while (array3D[tempJ][tempK+1]!=rectangularColor){
                ++tempK;
            }
            
            while (array3D[tempJ+1][tempK]!=rectangularColor){
                ++tempJ;
            }
            queuePair.push_back(coordinatesPair(J-1, K-1, tempJ+1, tempK+1));
            //array3D[J][K]=obstacleImage;
            //array3D[tempJ][tempK]=obstacleImage;
            //std::cout<<J<<","<<K<<" ; "<<tempJ<<","<<tempK<<std::endl;
            queue.pop();
        }
        else if(queue.front().z==2){
            while (array3D[tempJ+1][tempK]!=rectangularColor){
                ++tempJ;
            }
            queuePair.push_back(coordinatesPair(J-1, K-1, tempJ+1, tempK+1));
            //array3D[J][K]=obstacleImage;
            //array3D[tempJ][tempK]=obstacleImage;
            //std::cout<<J<<","<<K<<" ; "<<tempJ<<","<<tempK<<std::endl;
            queue.pop();
        }
        else if(queue.front().z==3){
            while (array3D[tempJ][tempK+1]!=rectangularColor){
                ++tempK;
            }
            queuePair.push_back(coordinatesPair(J-1, K-1, tempJ+1, tempK+1));
            //array3D[J][K]=obstacleImage;
            //array3D[tempJ][tempK]=obstacleImage;
            //std::cout<<J<<","<<K<<" ; "<<tempJ<<","<<tempK<<std::endl;
            queue.pop();
        }
        else if(queue.front().z==4){
            queuePair.push_back(coordinatesPair(J-1, K-1, tempJ+1, tempK+1));
            array3D[J][K]=obstacleImage;
            //array3D[tempJ][tempK]=obstacleImage;
            //std::cout<<J-1<<","<<K-1<<" ; "<<tempK+1<<","<<tempK+1<<std::endl;
            queue.pop();
        }
        
        
        
        
        
    }
}


void findpoints::preparePicture(){
    for (int i=0; i<map->getWidth(); i++) {
        array3D[i][0]=obstacleImage;
        array3D[i][map->getHeight()-1]=obstacleImage;
    }
    for (int i=0; i<map->getHeight(); i++) {
        array3D[0][i]=obstacleImage;
        array3D[map->getWidth()-1][i]=obstacleImage;
    }
}

void findpoints::findDiagonals(){
    createArray();
    preparePicture();
    findPone();
    stageOne();
    findPtwo();
    stageTwo();
    
    
    std::cout<<queuePair.size()<<std::endl;
    for (int k=0; k<map->getWidth() ; ++k) {
        for (int j=0; j<map->getHeight() ; ++j) {
            map->setPixel8U(k,j,array3D[k][j]);
        }
    }
}

