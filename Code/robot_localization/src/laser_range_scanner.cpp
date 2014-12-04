//
//  range_scanner.cpp
//  laser_range_scanner
//
//  Created by Jannik Gade on 01/12/14.
//
//

#include "laser_range_scanner.h"

/*****************************************************************************************
 *  Constructor (also initializes csv_reader class)
 *****************************************************************************************/
laser_range_scanner::laser_range_scanner(std::string name):csv_reader(name){

}

/*****************************************************************************************
 *  Do a complete scan and return a vector containing the points
 *****************************************************************************************/
std::vector<pixel> laser_range_scanner::scan(){
    pixel convert_from_radial(0,10);
    float angle = 235;
    float PI = 3.14159265;
    if (number_of_scans<width) {
        for (int i = 0; i<height; i++) {
            convert_from_radial.set_pixel_x_y((float)stoi(string_array[i][number_of_scans])*sin(-angle*(PI/180)), (float)stoi(string_array[i][number_of_scans])*cos(-angle*(PI/180)));
            single_scan.push_back(convert_from_radial);
            angle+=0.36;
        }
        
        number_of_scans++;
    }
    std::vector<pixel> temp;
    return single_scan;
}

