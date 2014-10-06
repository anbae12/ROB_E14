#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include <cmath>
#include <algorithm>
using namespace rw::sensor;
using namespace rw::loaders;



///////////////////////// INIT /////////////////////////
int current_pos_x=0;
int current_pos_y=0;
int temp_current_pos_x=0;
int temp_current_pos_y=0;
///////////////////////// START/END /////////////////////////
int q_start_x = 00;
int q_start_y = 00;
int q_goal_x = 00;
int q_goal_y = 00;
///////////////////////// SET DIRECTORY /////////////////////////
std::string andersind= "/Users/Anders/Documents/Robotteknologi/5. semester/ROB/Programming problem/xCode_the_cup_collector/Bane1.pgm";
std::string andersout= "/Users/Anders/Documents/Robotteknologi/5. semester/ROB/Programming problem/xCode_the_cup_collector/test_out.pgm";
std::string filenameind = andersind;
std::string filenameout = andersout;

///////////////////////// MAIN /////////////////////////
int main() {
    
    std::cout << "Loading image..." << std::endl;
    Image* img = PPMLoader::load(filenameind);
    int channel = 0; // allways 0 on grayscale image
    
///////////////////////// FUNCTIONS /////////////////////////

    
    
    
    

///////////////////////// END OF FUNCTIONS /////////////////////////
img->saveAsPGM(filenameout);
delete img;
};