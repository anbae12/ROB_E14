//
//  robot.cpp
//  CUP_COLLECTOR
//
//  Created by Jannik Gade on 26/11/14.
//
//

/*****************************************************************************************
 *  Directions:      -------------          -------------
 *                  | NW | N | NE |         | 1 | 2 | 3 |
 *                   -------------          -------------
 *                  | W  | X | E  |   ==>   | 4 | 5 | 6 |
 *                   -------------          -------------
 *                  | SW | S | SE |         | 7 | 8 | 9 |
 *                   -------------          -------------
 *****************************************************************************************/

#define NW  1
#define N   2
#define NE  3
#define W   4
#define X   5
#define E   6
#define SW  7
#define S   8
#define SE  9

#define DOWN        1
#define UP          2
#define L_TURN_DOWN 3
#define L_TURN_UP   4

#define BLACK   0
#define WHITE   255
#define PI      3.1415926535

#include "robot.h"

cup_robot::cup_robot(unsigned int init_x, unsigned int init_y, unsigned int init_radius, Image *img){
    x_pos = init_x;
    y_pos = init_y;
    radius = init_radius;
    map = img;
    walked_pixels = 0;
}

/*****************************************************************************************
 *  Validates the move: position has to be within the image, and be free (white).
 *****************************************************************************************/
bool cup_robot::validate_move(int x, int y){
    // test if move is within image
    if (x>=0&&x<map->getWidth()&&y>=0&&y<map->getHeight()) {
        // only pixels that are white are free
        if(map->getPixelValuei(x, y, channel)!=black)
            return true;
        else
            return false;
    }
    return false;
}

/*****************************************************************************************
 *  Moves the robot in x-direction. Forward: 1 Backward:-1.
 *****************************************************************************************/
bool cup_robot::move_x_direction(int direction){
    if (validate_move(x_pos+direction,y_pos)) {
        x_pos+=direction;
        walked_pixels++;
        return true;
    }
    std::cout << "Invalid move in x direction!\n";
    return false;
}

/*****************************************************************************************
 *  Moves the robot in y-direction. Up: -1 Down: 1
 *****************************************************************************************/
bool cup_robot::move_y_direction(int direction){
    if (validate_move(x_pos,y_pos+direction)) {
        y_pos+=direction;
        walked_pixels++;
        return true;
    }
    std::cout << "Invalid move in y direction!\n";
    return false;
}


/*****************************************************************************************
 *  Returns the current x position of the robot.
 *****************************************************************************************/
int cup_robot::get_current_x(void){
    return x_pos;
}

/*****************************************************************************************
 *  Returns the current y position of the robot.
 *****************************************************************************************/
int cup_robot::get_current_y(void){
    return y_pos;
}

/*****************************************************************************************
 *  Get number of walked pixels.
 *****************************************************************************************/
unsigned int cup_robot::get_walked_pixels(void){
    return walked_pixels;
}

/*****************************************************************************************
 *  Find free direction. Used four connectivity pixels - see definitions at top.
 *****************************************************************************************/
int cup_robot::find_direction_4C(void){
    
    // Test 4 connectivity pixels first:
    // Go north
    if (validate_move(x_pos, y_pos-1))
        return N;
    // Go south
    else if (validate_move(x_pos, y_pos+1))
        return S;
    // Go east
    else if (validate_move(x_pos-1, y_pos))
        return W;
    // Go west
    else if (validate_move(x_pos+1, y_pos))
        return E;
    // return X, indicates that the current pixel is the only one free
    else
        return X;
        
}

/*****************************************************************************************
 *  Find free direction. Used eight connectivity pixels - see definitions at top.
 *****************************************************************************************/
int cup_robot::find_direction_8C(void){
    // Test 4 connectivity pixels first:
    // Go north
    if (validate_move(x_pos, y_pos-1))
        return N;
    // Go south
    else if (validate_move(x_pos, y_pos+1))
        return S;
    // Go east
    else if (validate_move(x_pos-1, y_pos))
        return W;
    // Go west
    else if (validate_move(x_pos+1, y_pos))
        return E;
    // Now test remainding 4:
    // Go northwest
    else if (validate_move(x_pos-1, y_pos-1))
        return NW;
    // Go northeast
    else if (validate_move(x_pos+1, y_pos-1))
        return NE;
    // Go southwest
    else if (validate_move(x_pos-1, y_pos+1))
        return SW;
    // Go southwest
    else if (validate_move(x_pos+1, y_pos+1))
        return SE;
    // return X, indicates that the current pixel is the only one free
    else
        return X;
    
}

/*****************************************************************************************
 *  Find free direction from pixel. Used eight connectivity pixels - see definitions at top.
 *****************************************************************************************/
int cup_robot::find_direction_8C(int x, int y){
    // Test 4 connectivity pixels first:
    // Go north
    if (validate_move(x, y-1))
        return N;
    // Go south
    else if (validate_move(x, y+1))
        return S;
    // Go east
    else if (validate_move(x-1, y))
        return W;
    // Go west
    else if (validate_move(x+1, y))
        return E;
    // Now test remainding 4:
    // Go northwest
    else if (validate_move(x-1, y-1))
        return NW;
    // Go northeast
    else if (validate_move(x+1, y-1))
        return NE;
    // Go southwest
    else if (validate_move(x-1, y+1))
        return SW;
    // Go southwest
    else if (validate_move(x+1, y+1))
        return SE;
    // return X, indicates that the current pixel is the only one free
    else
        return X;

}


/*****************************************************************************************
 *  Find free direction using 4 point connectivity. Ignores the free pixels in the
 *  direction you came from.
 *****************************************************************************************/
int cup_robot::find_direction_4C_directed(int direction_to_ignore){
    // Test 4 connectivity pixels:
    // Go north
    if (validate_move(x_pos, y_pos-1)&&direction_to_ignore!=N)
        return N;
    // Go south
    else if (validate_move(x_pos, y_pos+1)&&direction_to_ignore!=S)
        return S;
    // Go east
    else if (validate_move(x_pos-1, y_pos)&&direction_to_ignore!=W)
        return W;
    // Go west
    else if (validate_move(x_pos+1, y_pos)&&direction_to_ignore!=E)
        return E;
    else
        return X;
}


/*****************************************************************************************
 *  Finds the opposite direction of robot.
 *****************************************************************************************/
int cup_robot::find_opposite_direction(int direction){
    // Go north
    if (direction==N)
        return S;
    // Go south
    else if (direction==S)
        return N;
    // Go east
    else if (direction==W)
        return E;
    // Go west
    else if (direction==E)
        return W;
    else
        return X;
}


/*****************************************************************************************
 *  Color current pixel.
 *****************************************************************************************/
void cup_robot::color_current_pixel(unsigned int color=128){
    map->setPixel8U(x_pos, y_pos, color);
}

/*****************************************************************************************
 *  Color traversed pixels.
 *****************************************************************************************/
void cup_robot::color_traversed_pixels(unsigned int color=128, int direction=N){
    // direction of robot is up or down, color left to right
    if (direction==N||direction==S) {
        for (int i=x_pos-radius; i<x_pos+radius+1; i++) {
            if (validate_move(i, y_pos)) {
                map->setPixel8U(i, y_pos, color);
            } else
                ;//std::cout << "Cannot color pixel!\n";
        }
    }
    // direction of robot is left or right, color up and down
    else if (direction==E||direction==W) {
        for (int i=y_pos-radius; i<y_pos+radius+1; i++) {
            if (validate_move(x_pos, i)) {
                map->setPixel8U(x_pos, i, color);
            } else
                ;//std::cout << "Cannot color pixel!\n";
        }
    }
}

/*****************************************************************************************
 *  Tests if pixel is within reach of sensor
 *****************************************************************************************/
bool cup_robot::within_sensor_reach(int goal_x, int goal_y, unsigned int direction=N, unsigned int range=1){
    // direction of robot is up or down, color left to right
    if (direction==N||direction==S) {
        for (int i=x_pos-range; i<x_pos+range+1; i++) {
            if (i==goal_x&&y_pos==goal_y) {
                return true;
            } else
                ;//std::cout << "Cannot color pixel!\n";
        }
    }
    // direction of robot is left or right, color up and down
    else if (direction==E||direction==W) {
        for (int i=y_pos-range; i<y_pos+range+1; i++) {
            if (i==goal_y&&goal_x==x_pos) {
                return true;
            } else
                ;//std::cout << "Cannot color pixel!\n";
        }
    }
    return false;
}

/*****************************************************************************************
 *  Covers a vertex.
 *****************************************************************************************/
void cup_robot::cover_vertex(unsigned int goal_x, unsigned int goal_y){
    bool finished = false;
    bool obstacle = false;
    int traversal_type = DOWN;
    int walked_pixels_limit = 525;
    
    map->setPixel8U(9, 8, 150);
    
    if (find_direction_8C()==X) {
        std::cout << "No available pixels from start!" << std::endl;
        return;
    }
    if (find_direction_8C(goal_x, goal_y)==X) {
        std::cout << "No available pixels from goal!" << std::endl;
        return;
    }
    
    color_traversed_pixels(128,S);
    color_current_pixel(100);
    
    
    
    while (!finished) {
        obstacle = false;
        
        switch (traversal_type) {
            case DOWN:
            {
                std::cout << "Going south in a straight line!" << std::endl;
                while (!obstacle) {
                    if (walked_pixels>walked_pixels_limit) {
                        std::cout << "walked pixels: " << walked_pixels << std::endl;
                        finished = true;
                    }
                    
                    if (move_y_direction(1))
                        ;
                    else
                        obstacle = true;
                    color_traversed_pixels(128,S);
                    color_current_pixel(100);
                    
                    if (within_sensor_reach(goal_x, goal_y, S, radius)) {
                        finished = true;
                    }
                }
                traversal_type = L_TURN_DOWN;
            }
            case L_TURN_DOWN:
            {
                int temp_x_pos = x_pos;
                int temp_y_pos = y_pos;
                
                while (sqrt(pow(x_pos-temp_x_pos, 2)+pow(y_pos-temp_y_pos, 2))<radius*2) {
                    // test if east position is available
                    if (validate_move(x_pos+1, y_pos)) {
                        move_x_direction(1);
                        color_traversed_pixels(128,E);
                        color_current_pixel(100);
                        if (within_sensor_reach(goal_x, goal_y, E, radius)) {
                            std::cout << "here!\n";
                            finished = true;
                        }
                    }
                    // test if northeast position is available
                    else if (validate_move(x_pos+1, y_pos-1)) {
                        std::cout << "probe!" << std::endl;
                        move_y_direction(-1);
                        move_x_direction(1);
                        color_traversed_pixels(128,E);
                        color_current_pixel(100);
                        if (within_sensor_reach(goal_x, goal_y, E, radius)) {
                            std::cout << "here!\n";
                            finished = true;
                        }
                    }
                    
                }
                // color the last pixels
                color_traversed_pixels(128,N);
                if (within_sensor_reach(goal_x, goal_y, N, radius)) {
                    std::cout << "\n\n\nhere!\n\n\n";
                    finished = true;
                }
                
                color_current_pixel(100);
                
                obstacle = false;
                std::cout << "Turning east!\n";
                
                traversal_type = UP;
                break;
            }
            case UP:
            {
                if (walked_pixels>walked_pixels_limit) {
                    std::cout << "walked pixels: " << walked_pixels << std::endl;
                    return;
                }
                std::cout << "Going north in a straight line!" << std::endl;
                while (!obstacle) {
                    if (walked_pixels>walked_pixels_limit) {
                        std::cout << "walked pixels: " << walked_pixels << std::endl;
                        finished = true;
                    }
                    
                    if (move_y_direction(-1))
                        ;
                    else
                        obstacle = true;
                    color_traversed_pixels(128,N);
                    color_current_pixel(100);
                    
                    if (within_sensor_reach(goal_x, goal_y, N,radius)) {
                        finished = true;
                    }
                }
                traversal_type = L_TURN_UP;
            }
            case L_TURN_UP:
            {
                
                obstacle = false;
                int temp_x_pos = x_pos;
                int temp_y_pos = y_pos;
                
                while (sqrt(pow(x_pos-temp_x_pos, 2)+pow(y_pos-temp_y_pos, 2))<radius*2) {
                    // test if east position is available
                    if (validate_move(x_pos+1, y_pos)) {
                        move_x_direction(1);
                        color_traversed_pixels(128,E);
                        color_current_pixel(100);
                        if (within_sensor_reach(goal_x, goal_y, E,radius)) {
                            finished = true;
                        }
                    }
                    // test if southeast position is available
                    else if (validate_move(x_pos+1, y_pos+1)) {
                        std::cout << "probe!" << std::endl;
                        move_y_direction(1);
                        move_x_direction(1);
                        color_traversed_pixels(128,E);
                        color_current_pixel(100);
                        if (within_sensor_reach(goal_x, goal_y, E, radius)) {
                            finished = true;
                        }
                    }
                    
                }
                
                // color the last pixels
                color_traversed_pixels(128,E);
                if (within_sensor_reach(goal_x, goal_y, E, radius)) {
                    std::cout << "\n\n\nhere!\n\n\n";
                    finished = true;
                }
                
                color_current_pixel(100);
                
                
                traversal_type = DOWN;
                break;
                
            }
                
            default:
                break;
        }
    }
}

/*****************************************************************************************
 *  360 degrees range scanner for cups at the distance specified.
 *****************************************************************************************/
int cup_robot::cup_scanner(void)
{
    for (int i=0; i<360; i++) {
        radial_scanner(i, 10, 150);
    }
    return 0;
}

/*****************************************************************************************
 *  360 degrees range scanner for cups at the distance specified.
 *****************************************************************************************/
int cup_robot::radial_scanner(int direction, int range, int color) //function for finding nearest object at 'direction' degrees within 'range'.
{
    float radDir = direction*((PI) / (180)); //Convert direction from degrees to radians
    int checkX, checkY, checkXold = 0, checkYold = 0;
    if (x_pos+range<map->getWidth()&&y_pos+range<map->getHeight()&&x_pos-range>0&&y_pos-range>0) {
        for (int r = 0; r < range; r++){ //Each pixel in the given direction until 'range' has been reached, has its pixel value checked.
            checkX = cos(radDir)*r + x_pos;
            checkY = sin(radDir)*r + y_pos;
            
            //if the pixel value is '0' (black) and at least one coordinate is different from the previous coords, an object has been reached.
            if (map->getPixelValuei(checkX, checkY, channel) == color && (checkX != checkXold || checkY != checkYold)){
                std::cout << "\n\n\n\n\nFound a cup!\n\n\n\n\n";
                return r; //The range where the object is found is returned
            }
            else //no object was found
                map->setPixel8U(checkX, checkY, 50); //Set the pixel value of each pixel along the checked line to '0'
            checkXold = checkX; //Save the previous XY-coords
            checkYold = checkY;
        }
    }
    
    std::cout << "No obstacle was detected within the requested range." << std::endl;
    return 0;
}




