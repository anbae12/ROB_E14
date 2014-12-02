#include <iostream>
#include "Ransac.h"

using namespace std;

int main() {
	Ransac ransac;

	ransac.addPoint(2, 6);
	ransac.addPoint(1, 8);
	ransac.addPoint(1, 3);

	ransac.run();
	return 0;
}

