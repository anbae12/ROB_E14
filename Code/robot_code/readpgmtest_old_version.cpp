#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include "vector2D.h"

#define FALSE	0
#define TRUE	1

using namespace std;
using namespace rw::sensor;
using namespace rw::loaders;

//----------------------------------------------------

struct robot{
    int posX;
    int posY;
};

robot bug;
int dx = 10, dy = 10, dTheta = 0;
/*
int main(int argc, char** argv) {
    
    std::string filename = "box.pgm";
    
    std::cout << "loading image..." << std::endl;
    Image* img = PPMLoader::load(filename);
    
    // do stuff here
    int channel = 0; // always 0 on grayscale image
    int direction, range;
    
    //Pixel coordinates of the robot.
    bug.posX = 50;
    bug.posY = 50;
    vector2D test(bug.posX, bug.posY, *img);
    
    for (int j=50; j<100; j+=3) {
        for (int i = 0; i < 360; i++){
            test.vectorCheck(i, 50);
        }
        test.set_position(50, j);
    }
    
    img->saveAsPGM("testOut.pgm");
    
    cout << "saving image.." << endl;
    
    //delete img;
}
*/




#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include "utility"

using namespace rw::sensor;
using namespace rw::loaders;

using namespace std;

void cover_vertex(Image *img, unsigned int vertex_x_value, unsigned int vertex_y_value);

int main(int argc, char** argv) {
    std::string filename = "test.pgm";
    
    

    std::cout << "loading image..." << std::endl;
    Image* img = PPMLoader::load(filename);
    
    cover_vertex(img, 22, 22);
    
    std::cout << "saving image..." << std::endl;
    // save image
    img->saveAsPGM("testout.pgm");
        
    // cleanup
    //delete img;
}


//
// This function covers a rectangular vertex. Start in a corner
//
void cover_vertex(Image *img, unsigned int vertex_x_value, unsigned int vertex_y_value){
    
    bug.posX = vertex_x_value;
    bug.posY = vertex_y_value;
    vector2D test(bug.posX, bug.posY, *img);
    
    
    
    unsigned int channel = 0;
    unsigned int white = 255;
    unsigned int black = 0;
    unsigned int visited_pixel = 128;
    unsigned int visited_range_pixel = 100;
    bool finished = false;
    unsigned int next_x = vertex_x_value, next_y = vertex_y_value;
    int direction_x, direction_y;
    
    
    //find next empty pixel
    if(img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel){
        direction_x = 1;
        direction_y = 0;
    }
    else if (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel){
        direction_x = -1;
        direction_y = 0;
    }
    else if (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel){
        direction_x = 0;
        direction_y = 1;
    }
    else if (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel){
        direction_x = 0;
        direction_y = -1;
    }
    
    int iter = 0;
    while (!finished) {
        
        while (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel) {
            
            test.set_position(next_x, next_y);
            
            for (int i = 0; i < 360; i++){
                cout << "i'm here!" << endl;
                test.vectorCheck(i, 4);
            }
            
            img->setPixel8U(next_x,next_y,visited_pixel);
            if (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel) {
                next_x += direction_x;
                next_y += direction_y;
            } else
                break;
        }
        cout << "x: " << next_x << " y: " << next_y << endl;
        
        //go down
        if (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel) {
            direction_x = 0;
            direction_y = 1;
            img->setPixel8U(next_x,next_y+1,visited_pixel);
        }
        //go left
        else if (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel) {
            direction_x = -1;
            direction_y = 0;
            img->setPixel8U(next_x-1,next_y,visited_pixel);
        }
        //go up
        else if (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel) {
            direction_x = 0;
            direction_y = -1;
            img->setPixel8U(next_x,next_y-1,visited_pixel);
        }
        //go right
        else if (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel) {
            direction_x = 1;
            direction_y = 0;
            img->setPixel8U(next_x+1,next_y,visited_pixel);
        }
        else
            finished = true;
        iter++;
        if (img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==white||img->getPixelValuei(next_x+direction_x, next_y+direction_y, channel)==visited_range_pixel){
            next_x +=direction_x;
            next_y +=direction_y;
        }
    }
}




