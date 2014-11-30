#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include "vector2D.h"
#include "robot2D.h"

#define FALSE	0
#define TRUE	1

using namespace std;
using namespace rw::sensor;
using namespace rw::loaders;

//----------------------------------------------------

struct robot{
	int posX;
	int posY;
};

robot bug;
int dx = 10, dy = 10, dTheta = 0;

int main(int argc, char** argv) {

	std::string filename = "box.pgm";

	std::cout << "loading image..." << std::endl;
	Image* img = PPMLoader::load(filename);
	
	// do stuff here
	int channel = 0; // always 0 on grayscale image
	int direction, range;

	//Pixel coordinates of the robot.
	bug.posX = 50;
	bug.posY = 50;
	vector2D test(bug.posX, bug.posY, *img);

	for (int i = 0; i < 360; i++){
		test.vectorCheck(i, 100);
	}
	img->saveAsPGM("testOut.pgm");
	//while (true){ //simple menu for checking distances to objects
	//	cout << "Please enter direction in degrees: " << endl;
	//	cin >> direction;
	//	cout << endl << "Please enter range of search: " << endl;
	//	cin >> range;
	//	cout << endl << "Distance to nearest obstacle: " << test.vectorCheck(direction, range) << endl;
	//	cout << "saving image..." << endl;
	//	// save image
	//	img->saveAsPGM("testout.pgm");
	//}
	delete img;
	system("pause");
}

