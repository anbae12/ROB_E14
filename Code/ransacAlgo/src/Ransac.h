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
#include <cstdlib>

class Ransac {
public:
	Ransac() {}
	~Ransac() {}
	void run();
	void addPoint(uint x, uint y);
private:
	struct line {float a = 0, b = 0;};

	float calcDist(line line, pixel pixel);
	line calcLine(pixel point1, pixel point2);
	void printPoint(pixel point) { std::cout << "(" << point.get_x() << "," << point.get_y() << ")" << std::endl;}
	void algo();

	std::vector<pixel> points;
	std::vector<line> lines;
private:

};

#endif /* RANSAC_H_ */
