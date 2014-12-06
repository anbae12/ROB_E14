/*
 * Ransac.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: Lars Kristian Feddersen
 */

#include "Ransac.h"

void Ransac::run()
{
	points_temp = points;
	algo();
}

void Ransac::algo()
{
	float maxDist = 3, minInliers = 40, maxIterations = 10000, iterations = 0;
	std::vector<pixel> inliers;
	pixel point1, point2;
	line tempLine;

	srand(time(NULL));

	while(points.size() > minInliers && iterations < maxIterations)
	{
		iterations++;
		point1 = points[rand() % points.size()];
		point2 = points[rand() % points.size()];

		tempLine = calcLine(point1, point2);

		if (!isnanf(fabs(tempLine.a))) {
			for (uint i = 0; i < points.size(); i++)
				if (maxDist >= calcDist(tempLine, points[i]))
					inliers.push_back(points[i]);

			if (inliers.size() >= minInliers) {
				//LinearRegression reg(inliers);
				//tempLine.a = reg.getA();
				//tempLine.b = reg.getB();
				lines.push_back(tempLine);

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

void Ransac::drawLines()
{
	std::string imagePath = "";
	uint y, x;
	static Image img(800,800,Image::GRAY,Image::Depth16U);
	// initialize to white image
	for(int x=0;x<img.getWidth();x++)
		for(int y=0;y<img.getWidth();y++)
			img.setPixel16U(x,y,65000);

	for (uint i = 0; i < lines.size(); i++) {
		//std::cout << atan(lines[i].a)*180/PI << std::endl;
		if (atan(lines[i].a)*180/PI < 45. && atan(lines[i].a)*180/PI > -45.) {
			for(x = 0; x < img.getWidth(); x++) {
				y = lines[i].a*x + lines[i].b;
				if (y < img.getHeight() && y > 0) {
					img.setPixel16U(x,y,0);
					//std::cout << "(" << x << "," << y << ")" << std::endl;
				}
			}
		} else {
			for(y = 0; y < img.getHeight(); y++) {
				if (isinff(lines[i].a))
					x = lines[i].b;
				else
					x = (y-lines[i].b)/lines[i].a;

				if (x < img.getWidth() && x > 0) {
					img.setPixel16U(x,y,0);
					//std::cout << "(" << x << "," << y << ")" << std::endl;
				}
			}
		}
	}

	for (uint i = 0; i < points_temp.size(); i++) {
		x = points_temp[i].get_x();
		y = points_temp[i].get_y();
		//std::cout << "(" << x << "," << y << ")" << std::endl;
		if ((x < img.getWidth()-1 && x > 0) && (y < img.getHeight()-1 && y > 0)) {
			img.setPixel16U(x,y,65000/2);
		}
	}

	imagePath = "images/ransac"+std::to_string(imagesNumber)+".pgm";

	img.saveAsPGMAscii(imagePath);
	imagesNumber++;
	lines.clear();
	points.clear();
	points_temp.clear();
}
