#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include "math.h"

using namespace std;
using namespace rw::sensor;
using namespace rw::loaders;

#define PI		3.1415926535

class vector2D
{
public:
	vector2D(int, int, Image &image);
	int vectorCheck(int direction, int range);
    void set_position(int x, int y);
private:
	int posX, posY;
	Image img;
};