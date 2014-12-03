//
//  range_scanner.h
//  laser_range_scanner
//
//  Created by Jannik Gade on 01/12/14.
//
//

#ifndef __laser_range_scanner__laser_range_scanner__
#define __laser_range_scanner__laser_range_scanner__

#include <iostream>
#include "convert.h"
#include <vector>
#include "pixel.h"
#include "math.h"

class laser_range_scanner:public csv_reader {
private:
    int number_of_scans = 0;
    std::vector<pixel> single_scan;
public:
    laser_range_scanner(std::string in_filename);
    laser_range_scanner();
    std::vector<pixel> scan();
    
};


#endif 

