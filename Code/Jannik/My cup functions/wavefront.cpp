//
//  wavefront.cpp
//  CUP_COLLECTOR
//
//  Created by Jannik Gade on 29/11/14.
//
//

#include "wavefront.h"


/*****************************************************************************************
 *  Constructor
 *****************************************************************************************/
wavefront::wavefront(Image *img){
    map = img;
    
    // Generate a mask the matches the dimensions of the image.
    wavefront_mask = new int*[map->getHeight()];
    for (int i = 0; i < map->getHeight(); i++)
        wavefront_mask[i] = new int[map->getWidth()];
    
    initialize_to_zero_and_ones();
}

/*****************************************************************************************
 *  Default Constructor
 *****************************************************************************************/
wavefront::wavefront(){};

/*****************************************************************************************
 *  Destructor
 *****************************************************************************************/
wavefront::~wavefront(){
    
    
    std::cout << "Destroying wavefront object!\n";
    for (int i = 0; i < map->getHeight(); i++) {
        delete [] wavefront_mask[i];
        wavefront_mask[i] = nullptr;
    }
    delete [] wavefront_mask;
    wavefront_mask = nullptr;
    
}

/*****************************************************************************************
 *  Color the pixel
 *****************************************************************************************/
void wavefront::color_pixel(int pixel_x, int pixel_y, int value){
    map->setPixel8U(pixel_x, pixel_y, value);
}

/*****************************************************************************************
 *  Color the pixel
 *****************************************************************************************/
void wavefront::color_pixel(pixel p, int value){
    map->setPixel8U(p.get_x(), p.get_y(), value);
}

/*****************************************************************************************
 *  Initializes the mask to zeros and ones for free space and obstacles respectively.
 *  Also padds the obstacles with extra ones
 *****************************************************************************************/
void wavefront::initialize_to_zero_and_ones(){
    //Init the grid with zero for free space and ones for obstacles.
    
    for (int y = 0; y < map->getHeight(); y++)
        for (int x = 0; x < map->getWidth(); x++)
            if (map->getPixelValuei(x, y, 0) == 0) {
                wavefront_mask[y][x] = 1;
                
                 //Make the obstacles bigger
                 for (int i = y - 4; i <= y + 4; i++) {
                     for (int j = x - 4; j <= x + 4; j++) {
                         if (j <= map->getWidth() - 1 && i <= map->getHeight() - 1 && j >= 0 && i >= 0) {
                             wavefront_mask[i][j] = 1;
                             /*
                             if (map->getPixelValuei(j, i, 0) != 0){
                                 map->setPixel8U(j, i, 100);
                             }
                              */
                         }
                     }
                 }
                 
            } else if (wavefront_mask[y][x] != 1) {
                wavefront_mask[y][x] = 0;
            }
    
    //
    for (int y = 0; y < map->getHeight(); y++)
        for (int x = 0; x < map->getWidth(); x++)
            if (wavefront_mask[y][x] == 1)
                map->setPixel8U(x, y, 0);
    
    
}

/*****************************************************************************************
 *  Makes a wavefront from one or two points
 *****************************************************************************************/

void wavefront::make_wavefront(pixel set_goal_1, pixel set_goal_2=pixel(-1,-1)){
    
    goal_1 = set_goal_1;
    goal_2 = set_goal_2;
    
    if (set_goal_1) {
        wavefront_mask[goal_1.get_y()][goal_1.get_x()] = 2; // Label the goal with a two.
        wavefrontQueue.push(goal_1); // Start the wavefront at goal pos.
    }
    
    if (set_goal_2) {
        wavefront_mask[goal_2.get_y()][goal_2.get_x()] = 2; // Label the goal with a two.
        wavefrontQueue.push(goal_2); // Start the wavefront at goal pos.
    }
    
    if (!set_goal_1&&!set_goal_2) {
        std::cout << "Error: no goal was set in wavefront algorithm!" << std::endl;
        return;
    }
    
    pixel tempPos, currentPos, tempBestPos;	// Used for checking x,y around of the current pixel and storring temp pos
    
    while (!wavefrontQueue.empty())
    {
        // Get current pos for cheking.
        currentPos.set_pixel_x_y(wavefrontQueue.front().get_x(), wavefrontQueue.front().get_y());
        
        // Check arround the pixel
        for (int i = 0; i < 4; i++)
        {
            switch (i){
                case 0:
                    tempPos.set_pixel_x_y(currentPos.get_x(), currentPos.get_y() - 1);
                    break;
                case 1:
                    tempPos.set_pixel_x_y(currentPos.get_x(), currentPos.get_y() + 1);
                    break;
                case 2:
                    tempPos.set_pixel_x_y(currentPos.get_x() - 1, currentPos.get_y());
                    break;
                case 3:
                    tempPos.set_pixel_x_y(currentPos.get_x() + 1, currentPos.get_y());
                    break;
            }
            
            // Make sure it not will go off the picture.
            if (tempPos.get_x() <= map->getWidth() - 1 && tempPos.get_y() <= map->getHeight() - 1 && tempPos.get_x() >= 0 && tempPos.get_y() >= 0) {
                //Is that pos free.
                if (wavefront_mask[tempPos.get_y()][tempPos.get_x()] == 0) {
                    wavefront_mask[tempPos.get_y()][tempPos.get_x()] = wavefront_mask[currentPos.get_y()][currentPos.get_x()] + 1; // Then increment the wavevalue and insert it.
                    wavefrontQueue.push(tempPos); // And push that pos for further checking.
                }
            }
        }
        
        //Done with that pixel, remove it from the queue
        wavefrontQueue.pop();
    }
    
    
}


/*****************************************************************************************
 *  Makes a wavefront from one or two points
 *****************************************************************************************/
void wavefront::make_wavefront(unsigned int set_x_1, unsigned int set_y_1, unsigned int set_x_2, unsigned int set_y_2){
    pixel g1(set_x_1,set_y_1), g2(set_x_2,set_y_2);
    std::cout << "x1: " << g1.get_x() << " y1: " << g1.get_y() << " x2: " << g2.get_x() << " y2: " << g2.get_y() << std::endl;
    make_wavefront(g1,g2);

}

/*****************************************************************************************
 *  Saves the wavefront array as pixels in the map
 *****************************************************************************************/
void wavefront::save_wavefront_to_map(int gradient_scale){
    for (int i = 0; i < map->getHeight(); i++)
        for (int j = 0; j < map->getWidth(); j++)
            color_pixel(j, i, wavefront_mask[i][j]/gradient_scale);
}

/*****************************************************************************************
 *  Prints the wavefront array
 *****************************************************************************************/
void wavefront::print_wavefront_array(){
    //std::cout << "HERE! h: " << map->getHeight() << " w: " << map->getWidth() << std::endl;
    for (int i = 0; i < map->getHeight(); i++) {
        
        for (int j = 0; j < map->getWidth(); j++) {
            //std::cout << i << " " << j << " ";
            std::cout << wavefront_mask[i][j] << "\t";
        }
        std::cout << "\n";
    }
}