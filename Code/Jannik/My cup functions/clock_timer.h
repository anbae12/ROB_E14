//
//  clock_timer.h
//
//  Created by Anders Launer Baek on 12/09/14.
//  Copyright (c) 2014 Anders Launer Baek. All rights reserved.
//

/*
 remember to include header: 
 #include "clock_timer.h"
 
 Useage:
 
 clock_timer timerrecord;
 timerrecord.start_timer();
 timerrecord.stop_timer();
 */

#ifndef __timer_clock__clock_timer__
#define __timer_clock__clock_timer__
#include <ctime>
#include <iostream>
class clock_timer{
public:
    void start_timer();
    void stop_timer();
    std::clock_t time;
    std::clock_t start;
    long double duration;
};

#endif /* defined(__timer_clock__clock_timer__) */