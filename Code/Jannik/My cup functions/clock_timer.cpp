//
//  clock_timer.cpp
//  timer_clock
//
//  Created by Anders Launer Baek on 12/09/14.
//  Copyright (c) 2014 Anders Launer Baek. All rights reserved.
//

#include "clock_timer.h"


void clock_timer::start_timer(){
    start = std::clock();
}

void clock_timer::stop_timer(){
    duration=( std::clock() - start ) / (long double) CLOCKS_PER_SEC*1000;
    //std::cout<< "Time: "<<time<<"[ms]"<< std::endl;
}