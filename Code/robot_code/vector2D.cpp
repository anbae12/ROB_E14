#include "vector2D.h"

vector2D::vector2D(int x, int y, Image &image)
{
	posX = x;
	posY = y;
	img = image;
	cout << "posX: " << posX << endl << "posY: " << posY << endl;
}

void vector2D::set_position(int x, int y)
{
    posX = x;
    posY = y;
    cout << "posX: " << posX << endl << "posY: " << posY << endl;
}

int vector2D::vectorCheck(int direction, int range) //function for finding nearest object at 'direction' degrees within 'range'. 
{
	
	float radDir = direction*((PI) / (180)); //Convert direction from degrees to radians
	int checkX, checkY, checkXold = 0, checkYold = 0;
    if (posX+range<img.getWidth()&&posY+range<img.getHeight()&&posX-range>0&&posY-range>0) {
        for (int r = 0; r < range; r++){ //Each pixel in the given direction until 'range' has been reached, has its pixel value checked.
            checkX = cos(radDir)*r + posX;
            checkY = sin(radDir)*r + posY;
            if (img.getPixelValuei(checkX, checkY, 0) == 0 && (checkX != checkXold || checkY != checkYold)) //if the pixel value is '0' (black) and at least one coordinate is different from the previous coords, an object has been reached.
                return r; //The range where the object is found is returned
            else //no object was found
                img.setPixel8U(checkX, checkY, 100); //Set the pixel value of each pixel along the checked line to '0'
            checkXold = checkX; //Save the previous XY-coords
            checkYold = checkY;
        }
    }
	
	cout << "No obstacle was detected within the requested range." << endl;
	return 0;
}