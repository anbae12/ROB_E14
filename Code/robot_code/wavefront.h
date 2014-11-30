//
//  wavefront.h
//  CUP_COLLECTOR
//
//  Created by Jannik Gade on 29/11/14.
//
//

#ifndef __CUP_COLLECTOR__wavefront__
#define __CUP_COLLECTOR__wavefront__

#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include "pixel.h"
#include "queue"
#include <vector>

using namespace rw::sensor;
using namespace rw::loaders;



class wavefront {
private:
    void initialize_to_zero_and_ones();
    std::queue<pixel> wavefrontQueue;				// Used for storing edges of the wave.
    pixel goal_1;
    pixel goal_2;
    void make_wavefront(pixel set_goal_1, pixel set_goal_2);
    void initialize_padding();
protected:
    Image *map;
    int** wavefront_mask;
public:
    wavefront(Image *img);
    wavefront();
    ~wavefront();
    void color_pixel(int pixel_x, int pixel_y, int value);
    void color_pixel(pixel p, int value);
    void make_wavefront(unsigned int set_x_1=-1, unsigned int set_y_1=-1, unsigned int set_x_2=-1, unsigned int set_y_2=-1);
    void save_wavefront_to_map(int gradient_scale=1);
    void print_wavefront_array();
};
#endif /* defined(__CUP_COLLECTOR__wavefront__) */
