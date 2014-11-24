#include <math.h>
#pragma once

#define PI		3.1415926535

class robot2D
{
public:
	robot2D(int,int,float);
	~robot2D();
	void robRot();
	void robTrans(int dX, int dY, float dTheta);
	robot2D operator * (const int**);
private:
	//transMatrix matrixArray[3];
};