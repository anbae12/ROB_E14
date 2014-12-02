/*
 * Ransac.h
 *
 *  Created on: Dec 2, 2014
 *      Author: Lars Kristian Feddersen
 */

#ifndef RANSAC_H_
#define RANSAC_H_

typedef unsigned int uint;

#include "pixel.h"
#include <iostream>
#include <vector>
#include <cmath>

class Ransac {
public:
	Ransac() {}
	~Ransac() {}
	void run();
	void addPoint(uint x, uint y);
private:
	struct line {
		float a = 0, b = 0;
	};

	float calcDist(line line, pixel pixel);
	line calcLine(uint x1, uint y1, uint x2, uint y2);
	void printCoord(uint pos) { std::cout << "(" << points[pos].get_x() << "," << points[pos].get_y() << ")" << std::endl;}
	std::vector<pixel> points;
private:

};

#endif /* RANSAC_H_ */
