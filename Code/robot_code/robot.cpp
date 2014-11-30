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

/*****************************************************************************************
 *  Constructor (also initializes wavefront class)
 *****************************************************************************************/
cup_robot::cup_robot(unsigned int init_x, unsigned int init_y, unsigned int init_radius, Image *img): wavefront(img){
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
 *  Moves the robot one step in x-direction. Forward: 1 Backward:-1.
 *****************************************************************************************/
bool cup_robot::move_x_direction(int direction){
    if (direction)
        if (validate_move(x_pos+direction,y_pos)) {
            x_pos+=direction;
            walked_pixels++;
            return true;
        }
    //std::cout << "Invalid move in x direction!\n";
    return false;
}

/*****************************************************************************************
 *  Moves the robot one step in y-direction. Up: -1 Down: 1
 *****************************************************************************************/
bool cup_robot::move_y_direction(int direction){
    if (direction)
        if (validate_move(x_pos,y_pos+direction)) {
            y_pos+=direction;
            walked_pixels++;
            return true;
        }
    //std::cout << "Invalid move in y direction!\n";
    return false;
}


/*****************************************************************************************
 *  Moves the robot one step in x and y-direction. Up: -1 Down: 1
 *****************************************************************************************/
bool cup_robot::move_x_y_direction(int direction_x, int direction_y){
    if (validate_move(x_pos+direction_x,y_pos+direction_y)) {
        x_pos+=direction_x;
        y_pos+=direction_y;
        walked_pixels++;
        return true;
    }
    std::cout << "Invalid move in y direction!\n";
    return false;
}

/*****************************************************************************************
 *  Moves the robot in a straight line from its current position to (x_1,y_1)
 *****************************************************************************************/
bool cup_robot::move_in_straight_line(int x_1, int y_1){

    float temp_x, temp_y, float_x_pos = x_pos, float_y_pos = y_pos;
    float unit_x_vector, unit_y_vector;
    int iterator = 1;
    
    // check if robot is at the specified location
    if (x_pos==x_1&&y_pos==y_1) {
        std::cout << "Robot is already at location!\n";
        return true;
    }
    
    //make directional unit vector
    if (abs(x_1-x_pos) > abs(y_1-y_pos)) {
        unit_x_vector = (float)(x_1-x_pos)/(float)abs(x_1-x_pos);
        unit_y_vector = (float)(y_1-y_pos)/(float)abs(x_1-x_pos);
    } else {
        unit_x_vector = (float)(x_1-x_pos)/(float)abs(y_1-y_pos);
        unit_y_vector = (float)(y_1-y_pos)/(float)abs(y_1-y_pos);
    }
    
    while (!((x_pos==x_1)&&(y_pos==y_1))) {
        
        temp_x = float_x_pos + iterator * unit_x_vector;
        temp_y = float_y_pos + iterator * unit_y_vector;
        
        std::cout << "old x: " << float_x_pos << " y: " << y_pos << std::endl;
        std::cout << "temp x: " << float_y_pos << " y: " << temp_y << std::endl;
        
        
        // test if there's a change in x or y-position
        if ((int)(temp_x+0.5)!=x_pos||(int)(temp_y+0.5)!=y_pos) {
            std::cout << "8CFTW!\n";
            move_x_y_direction((temp_x+0.5)-x_pos, (temp_y+0.5)-y_pos);
        }
        
        std::cout << "coloring pixel\n";
        color_pixel(x_pos, y_pos, 150);

        iterator++;
    }
    
    return true;
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
 *  Get number of collected cups.
 *****************************************************************************************/
unsigned int cup_robot::get_total_number_of_cups(void){
    return total_number_of_cups;
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
            if (i!=x_pos) {
                if (validate_move(i, y_pos))
                    map->setPixel8U(i, y_pos, color);
                else
                    ;//std::cout << "Cannot color pixel!\n";
            }
        }
    }
    // direction of robot is left or right, color up and down
    else if (direction==E||direction==W) {
        for (int i=y_pos-radius; i<y_pos+radius+1; i++) {
            if (i!=y_pos) {
                if (validate_move(x_pos, i))
                    map->setPixel8U(x_pos, i, color);
                else
                    ;//std::cout << "Cannot color pixel!\n";
            }
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
    bool obstacle = false;
    int traversal_type = DOWN;
    int direction_x, direction_y;
    bool finished = false;
    
    int temp_x_pos = x_pos;
    int temp_y_pos = y_pos;
    
    std::queue<pixel> cups;
    pixel temp_cup;
    pixel previous_pixel;
    
    // test if goal or start is trapped
    if (find_direction_8C()==X||find_direction_8C(goal_x, goal_y)==X) {
        std::cout << "Can't get to goal!" << std::endl;
        return;
    }
    
    color_traversed_pixels(128,S);
    color_current_pixel(100);
    
    while (!finished) {
        
        // scan for cups
        temp_cup = cup_scanner();
        // if cup is found, check if it already exists in queue
        if (!temp_cup.is_uninitialized()&&cups.empty())
            cups.push(temp_cup);
        else if (!temp_cup.is_uninitialized()&&!cups.empty())
            if (cups.back()!=temp_cup)
                cups.push(temp_cup);
        
        // if end of the vertex is within the radius of the robot
        if (within_sensor_reach(goal_x, goal_y, S, radius)) {
            finished = true;
        }
        // color the pixels covered by the robot based its direction
        if (direction_x) {
            color_traversed_pixels(128,E);
        } else
            color_traversed_pixels(128,S);
        
        color_current_pixel(100);
        
        move_x_direction(direction_x);
        move_y_direction(direction_y);
        
        switch (traversal_type) {
            case DOWN:
            {
                if (!obstacle) {
                    //std::cout << "DOWN!" << std::endl;
                    if (validate_move(x_pos, y_pos+1)) {
                        direction_x = 0;
                        direction_y = 1;
                    }
                    else {
                        direction_y = 0;
                        obstacle = true;
                    }
                } else
                    traversal_type = L_TURN_DOWN;
                
                // save for next switch case
                temp_x_pos = x_pos;
                temp_y_pos = y_pos;
                
                break;
            }
            case L_TURN_DOWN:
            {
                //std::cout << "L_TURN_DOWN!\n";
                
                if (sqrt(pow(x_pos-temp_x_pos, 2)+pow(y_pos-temp_y_pos, 2))<radius*2) {
                    // test if east position is available
                    if (validate_move(x_pos+1, y_pos)) {
                        direction_x = 1;
                        direction_y = 0;
                    }
                    // test if northeast position is available
                    else if (validate_move(x_pos+1, y_pos-1)) {
                        direction_x = -1;
                        direction_y = -1;
                    }
                } else
                    traversal_type = UP;
                
                obstacle = false;
                
                break;
            }
            case UP:
            {
                //std::cout << "UP!" << std::endl;
                
                if (!obstacle) {
                    if (validate_move(x_pos, y_pos-1)) {
                        direction_x = 0;
                        direction_y = -1;
                    }
                    else
                        obstacle = true;
                } else
                    traversal_type = L_TURN_UP;
                
                // save for next switch case
                temp_x_pos = x_pos;
                temp_y_pos = y_pos;
                break;
            }
            case L_TURN_UP:
            {
                //std::cout << "L_TURN_UP!\n";
                if (sqrt(pow(x_pos-temp_x_pos, 2)+pow(y_pos-temp_y_pos, 2))<radius*2) {
                    // test if east position is available
                    if (validate_move(x_pos+1, y_pos)) {
                        direction_x = 1;
                        direction_y = 0;
                    }
                    // test if southeast position is available
                    else if (validate_move(x_pos+1, y_pos+1)) {
                        direction_x = 1;
                        direction_y = 1;
                    }
                } else
                    traversal_type = DOWN;
                obstacle = false;
                break;
            }
            default:
                break;
        }
    }
    
    pixel print;
    // print cups
    while (!cups.empty()) {
        print = cups.front();
        std::cout << "found cups at x: " << print.get_x() << " y: " << print.get_y() << std::endl;
        color_pixel(print, 255);
        cups.pop();
    }
    
    
    
}

/*****************************************************************************************
 *  Collects a cup (pixel value 150) and sets the pixel to white. 
 *****************************************************************************************/
void cup_robot::collect_cup(int x, int y){
    int temp_x = x_pos, temp_y = y_pos;
    
    // move the robot towards the cup
    move_in_straight_line(x, y);
    
    // pick up cup (color the pixel white)
    color_pixel(x, y, WHITE);
    
    //cups_in_tray++;
    total_number_of_cups++;
    
    // if 20 cups are in tray, robot needs to empty tray (robot can carry 20 cups at the time)
    if (cups_in_tray.size()==20) {
        cups_in_tray.clear();
        empty_tray_and_return();
    }
    
    // move robot from the location of the cup and back to the original position
    move_in_straight_line(temp_x, temp_y);
    
    // if the return pixel is different from the departure pixel print error
    if (temp_x!=x_pos&&temp_y!=y_pos) {
        std::cout << "Robot is not in same position as when it went to empty cup tray!\n";
    }
}

/*****************************************************************************************
 *  360 degrees cup scanner with a radius of 1m (10 pixels)
 *****************************************************************************************/
pixel cup_robot::cup_scanner(void)
{
    pixel cup_location;
    for (int i=0; i<360; i+=2) {
        if (!radial_scanner(i, 10, 150).is_uninitialized()) {
            //std::cout << "\n\n\n\n\nFound a cup!\n\n\n\n\n";
            cup_location = radial_scanner(i, 10, 150);
            //std::cout << "cup location, x: " << cup_location.get_x() << " y: " << cup_location.get_y() << std::endl;
            return cup_location;
        }
    }
    return cup_location;
}

/*****************************************************************************************
 *  360 degrees range scanner at the distance specified.
 *****************************************************************************************/
pixel cup_robot::radial_scanner(int direction, int range, int color)
{
    pixel cup_location;
    //Convert direction from degrees to radians
    float radDir = direction*((PI) / (180));
    int checkX, checkY, checkXold = 0, checkYold = 0;
    if (x_pos+range<map->getWidth()&&y_pos+range<map->getHeight()&&x_pos-range>0&&y_pos-range>0) {
        //Each pixel in the given direction until 'range' has been reached, has its pixel value checked.
        for (int r = 0; r < range; r++){
            checkX = cos(radDir)*r + x_pos;
            checkY = sin(radDir)*r + y_pos;
            
            //if the pixel value is '0' (black) and at least one coordinate is different from the previous coords, an object has been reached.
            if (map->getPixelValuei(checkX, checkY, channel) == color && (checkX != checkXold || checkY != checkYold)){
                //std::cout << "\n\n\n\n\nFound a cup!\n\n\n\n\n";
                cup_location.set_pixel_x_y(checkX, checkY);
                return cup_location; //The range where the object is found is returned
            }
            else //no object was found
                ;//map->setPixel8U(checkX, checkY, 50); //Set the pixel value of each pixel along the checked line to '0'
            checkXold = checkX; //Save the previous XY-coords
            checkYold = checkY;
        }
    }
    
    //std::cout << "No obstacle was detected within the requested range." << std::endl;
    return cup_location;
}

/*****************************************************************************************
 *  Empties the tray and returns to the pixel
 *****************************************************************************************/
void cup_robot::empty_tray_and_return(void){
    std::cout << "you should write the function 'empty_tray_and_return'!\n";
}


/*****************************************************************************************
 *  Make the robot follow the wavefront
 *****************************************************************************************/
void cup_robot::follow_wavefront(){
    
    int temp_value;
    int direction_x, direction_y;
    
    pixel temp_path;
    
    while (wavefront_mask[y_pos][x_pos]!=2) {
        // save the wavefront value of the current position
        temp_value = wavefront_mask[y_pos][x_pos];
        std::cout << "temp: " << temp_value << std::endl;
        
        // save the current position
        temp_path.set_pixel_x_y(x_pos, y_pos);
        wavefront_path.push_front(temp_path);
        
        // find the lowest value in the 8 surrounding pixels
        for (int i=y_pos-1; i<y_pos+2; i++) {
            for (int j=x_pos-1; j<x_pos+2; j++) {
                //std::cout << wavefront_mask[i][j] << "\t";
                if (wavefront_mask[i][j]<temp_value) {
                    temp_value = wavefront_mask[i][j];
                    // find x direction
                    if (j-x_pos+1==0)
                        direction_x = -1;
                    else if (j-x_pos+1==2)
                        direction_x = 1;
                    else
                        direction_x = 0;
                    
                    // find y direction
                    if (i-y_pos+1==0)
                        direction_y = -1;
                    else if (i-y_pos+1==2)
                        direction_y = 1;
                    else
                        direction_y = 0;
                    std::cout << "direction x: " << direction_x << " y: " << direction_y << std::endl;
                }
            }
        }
        
        // move robot towards goal
        move_x_y_direction(direction_x, direction_y);
        color_pixel(x_pos, y_pos, 150);
        direction_x = direction_y = 0;
    }
}

void cup_robot::return_from_wavefront(){
    std::cout << "Returning to departure position" << std::endl;
    pixel temp_position;
    int direction_x;
    int direction_y;
    
    while (!wavefront_path.empty()) {
        temp_position = wavefront_path.front();
        direction_x = temp_position.get_x()-x_pos;
        direction_y = temp_position.get_y()-y_pos;
        
        // move robot
        move_x_y_direction(direction_x, direction_y);
        color_pixel(x_pos, y_pos, 110);
        direction_x = direction_y = 0;
        
        wavefront_path.pop_front();
    }
    
}


