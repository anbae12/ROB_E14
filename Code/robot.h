//
//  robot.h
//  CUP_COLLECTOR
//
//  Created by Jannik Gade on 26/11/14.
//
//

#ifndef __CUP_COLLECTOR__robot__
#define __CUP_COLLECTOR__robot__

#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include <math.h>

using namespace rw::sensor;
using namespace rw::loaders;

class cup_robot {
    unsigned int black = 0;
    unsigned int white = 255;
    int x_pos,y_pos;
    int radius = 4;
    Image *map;
    unsigned int channel = 0; //Default channel on image
    unsigned int walked_pixels;
    void color_current_pixel(unsigned int color);
    void color_traversed_pixels(unsigned int color, int direction);
    bool move_x_direction(int direction); //Forward: 1 Backward:-1
    bool move_y_direction(int direction); //Up: 1 Down:-1
    int find_direction_4C(void);
    int find_direction_8C();
    int find_direction_8C(int x, int y);
    int find_direction_4C_directed(int direction_to_ignore);
    int find_opposite_direction(int direction);
    bool validate_move(int x, int y);
    bool within_sensor_reach(int goal_x, int goal_y, unsigned int direction, unsigned int range);
    
    int cup_scanner(void);
    int radial_scanner(int direction, int range, int color);
    
public:
    cup_robot(unsigned int init_x, unsigned int init_y, unsigned int radius, Image *img);
    int get_current_x(void);
    int get_current_y(void);
    unsigned int get_walked_pixels(void);
    void cover_vertex(unsigned int goal_x, unsigned int goal_y);
};

#endif /* defined(__CUP_COLLECTOR__robot__) */
