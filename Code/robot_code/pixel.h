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
    
    friend const pixel operator*(const pixel& v, double s)
    {
        return pixel(v.x * s, v.y * s);
    }
    
    pixel& operator*=(double s)
    {
        x*=s;
        y*=s;
        return *this;
    }
    
    void set_pixel_x_y(int x_value, int y_value);
    int get_x(void);
    int get_y();
    bool is_uninitialized(void);
};


bool operator==(pixel &p1, pixel &p2);
bool operator!=(pixel &p1, pixel &p2);


/*
 friend const Vector2D operator*(const Vector2D& v, double s)
	{
 return Vector2D(v[0] * s, v[1] * s);
	}
 */

#endif /* defined(__CUP_COLLECTOR__pixel__) */

