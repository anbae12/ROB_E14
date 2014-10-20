#include <iostream>
#include <fstream>
#include <chrono>
#include <queue>
#include <iomanip>
#include "Image.hpp"
#include "PPMLoader.hpp"

using namespace std;
using namespace std::chrono;
using namespace rw::sensor;
using namespace rw::loaders;

struct vector2D {
public:
	vector2D() :x(-1), y(-1) {}
	vector2D(double x, double y) : x(x), y(y){};

	friend const vector2D operator-(const vector2D& a, const vector2D& b) { return vector2D(a.x - b.x, a.y - b.y); }
	friend double dist2(const vector2D& a, const vector2D& b){ return (b - a).norm2(); }

	int getX(){ return x; }
	int getY(){ return y; }

	void setXY(int x, int y){
		setX(x);
		setY(y);
	}

	void setX(int x){ this->x = x; }
	void setY(int y){ this->y = y; }
private:
	double x, y;
	double norm2() const { return sqrt(x*x + y*y); }
};



int main() {
	//Load the image
	string filename("complete_map_project.pgm");
	cout << "loading image..." << endl;
	Image* img = PPMLoader::load(filename);

	high_resolution_clock::time_point t1, t2;	// Used for timing of the different implenmentations.
	queue<vector2D> wavefrontQueue;				// Used for storing edges of the wave.
	int channel = 0, moves = 0;					// Allways zero in greyscale.
	vector2D tempPos, currentPos, tempBestPos;	// Used for checking x,y around of the current pixel and storring temp pos

	// Set start and end point.
	vector2D robot(480, 1362); // Lab start
	vector2D goal1(2860, 1320); // Lab end
	vector2D goal2(2400, 1320); // Lab end

	//vector2D robot(16, 37); // Lab start
	//vector2D goal1(125, 10); // Lab end
	//vector2D goal2(125, 10); // Lab end

	// Generate a mask the matches the dimensions of the image.
	int** wavefront = new int*[img->getHeight()];
	for (int i = 0; i < img->getHeight(); i++)
		wavefront[i] = new int[img->getWidth()];

	//Init the grid with zero for free space and ones for obstacles.
	for (int y = 0; y < img->getHeight(); y++)
		for (int x = 0; x < img->getWidth(); x++)
			if (img->getPixelValuei(x, y, channel) == 0) {
				wavefront[y][x] = 1;

				//Make the obstacles bigger
				for (int i = y - 4; i <= y + 4; i++) {
					for (int j = x - 4; j <= x + 4; j++) {
						if (j <= img->getWidth() - 1 && i <= img->getHeight() - 1 && j >= 0 && i >= 0) {
							wavefront[i][j] = 1;
							if (img->getPixelValuei(j, i, channel) != 0){
								img->setPixel8U(j, i, 200);
							}
						}
					}
				}
			} else if (wavefront[y][x] != 1) {
				wavefront[y][x] = 0;
			}

	wavefront[goal1.getY()][goal1.getX()] = 2; // Label the goal with a two.
	wavefront[goal2.getY()][goal2.getX()] = 2; // Label the goal with a two.
	wavefrontQueue.push(goal1); // Start the wavefront at goal pos.
	wavefrontQueue.push(goal2); // Start the wavefront at goal pos.

	//Make the wavefront.
	t1 = high_resolution_clock::now(); // Start timer
	while (!wavefrontQueue.empty())
	{
		// Get current pos for cheking. 
		currentPos.setXY(wavefrontQueue.front().getX(), wavefrontQueue.front().getY());

		// Check arround the pixel
		for (int i = 0; i < 4; i++)
		{
			switch (i){
			case 0:
				tempPos.setXY(currentPos.getX(), currentPos.getY() - 1);
				break;
			case 1:
				tempPos.setXY(currentPos.getX(), currentPos.getY() + 1);
				break;
			case 2:
				tempPos.setXY(currentPos.getX() - 1, currentPos.getY());
				break;
			case 3:
				tempPos.setXY(currentPos.getX() + 1, currentPos.getY());
				break;
			}

			// Make sure it not will go off the picture.
			if (tempPos.getX() <= img->getWidth() - 1 && tempPos.getY() <= img->getHeight() - 1 && tempPos.getX() >= 0 && tempPos.getY() >= 0) {
				//Is that pos free.
				if (wavefront[tempPos.getY()][tempPos.getX()] == 0) {
					wavefront[tempPos.getY()][tempPos.getX()] = wavefront[currentPos.getY()][currentPos.getX()] + 1; // Then increment the wavevalue and insert it.
					wavefrontQueue.push(tempPos); // And push that pos for further checking.
				}
			}
		}

		//Done with that pixel, remove it from the queue
		wavefrontQueue.pop();
	}
	t2 = high_resolution_clock::now(); // End timer

	//Fun facts
	cout << "Wavefront time: " << duration_cast<chrono::microseconds>(t2 - t1).count() << " microseconds" << endl;

	//Paint the start pos.
	img->setPixel8U(robot.getX(), robot.getY(), 300);
	//Plan the route
	t1 = high_resolution_clock::now(); // Start timer
	while (true)
	{
		//Get the robot pos as the temperary best pos.
		tempBestPos.setXY(robot.getX(), robot.getY());

		// Check arround the pixel
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++) {
				tempPos.setXY(robot.getX() + i, robot.getY() + j);
				// Make sure it not will go off the picture.
				if (tempPos.getX() <= img->getWidth() - 1 && tempPos.getY() <= img->getHeight() - 1 && tempPos.getX() >= 0 && tempPos.getY() >= 0) {
					//Check if temp is lesser the current wave value
					if (wavefront[tempPos.getY()][tempPos.getX()] < wavefront[robot.getY()][robot.getX()] && wavefront[tempPos.getY()][tempPos.getX()] < wavefront[tempBestPos.getY()][tempBestPos.getX()] && wavefront[tempPos.getY()][tempPos.getX()] > 1) {
						tempBestPos.setXY(tempPos.getX(), tempPos.getY());
					}
				}
			}

		//Move the robot
		moves++;
		robot.setXY(tempBestPos.getX(), tempBestPos.getY());
		//Paint the robot pos
		img->setPixel8U(robot.getX(), robot.getY(), 100);

		//If the robot has reach the goal then break out of the loop.
		if ((robot.getY() == goal1.getY() && robot.getX() == goal1.getX()) || (robot.getY() == goal2.getY() && robot.getX() == goal2.getX()))
			break;
	}
	t2 = high_resolution_clock::now(); // End timer

	//Fun facts
	cout << "Planning time: " << duration_cast<chrono::microseconds>(t2 - t1).count() << " microseconds" << endl;
	cout << "Moves: " <<  moves << endl;
	
	/*
	//Print how to wave expand to a text file
	ofstream waveExpand("waveExpand.txt");
	for (int y = 0; y < img->getHeight(); y++){
		for (int x = 0; x < img->getWidth(); x++){
			waveExpand << setfill(' ') << setw(4) << to_string(wavefront[y][x]) << "\t";
		}
		waveExpand << endl;
	}
	waveExpand.close();
	*/
	cout << "saving image..." << endl;
	// save image
	img->saveAsPGM("testout.pgm");

	// cleanup
	delete img;

	system("PAUSE");
}