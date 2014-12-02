/*
 * Ransac.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: Lars Kristian Feddersen
 */

#include "Ransac.h"

void Ransac::run()
{
	printCoord(0);
	printCoord(1);

	line temp = calcLine(points[0].get_x(), points[0].get_y(), points[1].get_x(), points[1].get_y());

	std::cout << "a: " << temp.a << std::endl;
	std::cout << "b: " << temp.b << std::endl;

	std::cout << "Dist: " << calcDist(temp, points[2]) << std::endl;
}

float Ransac::calcDist(line line, pixel pixel)
{
	return fabs(line.a*(float)pixel.get_x()+ line.b - (float)pixel.get_y()) / sqrt(pow(line.a, (float)2)+1);
}

Ransac::line Ransac::calcLine(uint x1, uint y1, uint x2, uint y2)
{
	line temp;

	temp.a = ((float)y2-(float)y1)/((float)x2-(float)x1);
	temp.b = (float)y1-temp.a*(float)x1;

	return temp;
}

void Ransac::addPoint(uint x, uint y)
{
	points.push_back(pixel(x, y));
}
