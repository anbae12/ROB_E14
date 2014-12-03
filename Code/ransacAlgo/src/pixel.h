//
//  pixel.h
//  CUP_COLLECTOR
//
//  Created by Jannik Gade on 28/11/14.
//
//

#ifndef __CUP_COLLECTOR__pixel__
#define __CUP_COLLECTOR__pixel__

#include <iostream>

class pixel {
private:
    int x;
    int y;
    
public:
    // constructor
    pixel(int x=-1, int y=-1);
    // copy constructor
    pixel(const pixel &p);
    pixel& operator=(const pixel &p);
    operator bool() const;
    
    void set_pixel_x_y(int x_value, int y_value);
    int get_x(void);
    int get_y();
    bool is_uninitialized(void);
};

bool operator==(pixel &p1, pixel &p2);
bool operator!=(pixel &p1, pixel &p2);



#endif /* defined(__CUP_COLLECTOR__pixel__) */

