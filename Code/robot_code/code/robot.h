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
#include "pixel.h"
#include "queue"
#include <vector>
//#include "wavefront.h"
#include "deque"
#include "findPoints.h"

using namespace rw::sensor;
using namespace rw::loaders;


class cup_robot: public findpoints {
protected:
    /*****************************************************************************************
     *  Variables
     *****************************************************************************************/
    unsigned int black = 0;
    int x_pos,y_pos;
    int radius = 4;
    //Image *map;
    unsigned int channel = 0; //Default channel on image
    unsigned int walked_pixels;
    //unsigned int cups_in_tray = 0;
    unsigned int total_number_of_cups = 0;
    
    std::vector<pixel> located_cups;
    std::vector<pixel> cups_in_tray;
    
    // stores the path walked by the wavefront
    std::deque<pixel> wavefront_path;
    
    /*****************************************************************************************
     *  Standard Functions
     *****************************************************************************************/
    void color_current_pixel(unsigned int color);
    void color_traversed_pixels(unsigned int color, int direction);
    bool move_x_direction(int direction); //Forward: 1 Backward:-1
    bool move_y_direction(int direction); //Up: 1 Down:-1
    bool move_x_y_direction(int direction_x, int direction_y);
    
    int find_direction_4C(void);
    int find_direction_8C();
    int find_direction_8C(int x, int y);
    int find_direction_4C_directed(int direction_to_ignore);
    int find_opposite_direction(int direction);
    bool validate_move(int x, int y);
    
    
    
    /*****************************************************************************************
     *  Sensor Functions
     *****************************************************************************************/
    bool within_sensor_reach(int goal_x, int goal_y, unsigned int direction, unsigned int range);
    pixel radial_scanner(int direction, int range, int color);
    void empty_tray_and_return(void);
    
public:
    /*****************************************************************************************
     *  Public Functions
     *****************************************************************************************/
    cup_robot(unsigned int init_x, unsigned int init_y, unsigned int radius, Image *img);
    int get_current_x(void);
    int get_current_y(void);
    unsigned int get_walked_pixels(void);
    void cover_vertex(unsigned int goal_x, unsigned int goal_y);
    pixel cup_scanner(void);
    bool move_in_straight_line(int x_1, int y_1);
    void collect_cup(int x, int y);
    unsigned int get_total_number_of_cups(void);
    void follow_wavefront();
    void return_from_wavefront();
};



#endif /* defined(__CUP_COLLECTOR__robot__) */
