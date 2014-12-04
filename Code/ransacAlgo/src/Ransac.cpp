/*
 * Ransac.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: Lars Kristian Feddersen
 */

#include "Ransac.h"

void Ransac::run()
{
	//for (uint i = 0; i < points.size(); i++)
	//	printPoint(points[i]);
	algo();
}

void Ransac::algo()
{
	uint maxDist = 2, minInliers = 2, maxIterations = 10, iterations = 0;
	std::vector<pixel> inliers;
	pixel point1, point2;
	line tempLine;

	srand(time(NULL));

	while(points.size() > minInliers || iterations > maxIterations)
	{
		iterations++;
		point1 = points[rand() % points.size()];
		point2 = points[rand() % points.size()];

		tempLine = calcLine(point1, point2);

		std::cout << "a: " << tempLine.a << " b: " << tempLine.b << std::endl;

		if (!isnanf(fabs(tempLine.a))) {
			for (uint i = 0; i < points.size(); i++)
				if (maxDist >= calcDist(tempLine, points[i]))
					inliers.push_back(points[i]);

			if (inliers.size() >= minInliers) {
				//RecomputerLine
				//update temp
				//Store line in vector line
				for (uint i = 0; i < inliers.size(); i++)
					for (uint j = 0; j < points.size(); j++)
						if (inliers[i] == points[j])
							points.erase(points.begin()+j);
			}
			inliers.clear();
		}
	}
}

float Ransac::calcDist(line line, pixel pixel)
{
	if (isinff(line.a))
		return fabs(line.b - pixel.get_x());
	else
		return fabs(line.a*(float)pixel.get_x()+ line.b - (float)pixel.get_y()) / sqrt(pow(line.a, (float)2)+1);
}

Ransac::line Ransac::calcLine(pixel point1, pixel point2)
{
	line temp;

	temp.a = ((float)point2.get_y() - (float)point1.get_y())/((float)point2.get_x() - (float)point1.get_x());

	if (isinff(temp.a))
		temp.b = point1.get_x();
	else
		temp.b = (float)point1.get_y() - temp.a*(float)point1.get_x();

	return temp;
}

void Ransac::addPoint(uint x, uint y)
{
	points.push_back(pixel(x, y));
}
