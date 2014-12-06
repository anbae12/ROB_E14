#include "laser_range_scanner.h"
#include "pixel.h"
#include "Ransac.h"

using namespace std;

int main(int argc, char **argv) {
	unsigned int x, y;
	laser_range_scanner scannerData("longrun_2.csv");
	Ransac findLines;

	std::vector<pixel> tempScan;

	for (int i = 0; i < 1705; i++) {
		tempScan = scannerData.scan();
		//cout << tempScan.size() << endl;
		while (!tempScan.empty()) {
			x = (tempScan.back().get_x()/10) + 350;
			y = (tempScan.back().get_y()/10) + 350;
			//std::cout << "(" << x << "," << y << ")" << std::endl;
			if (x != 350 && y != 350)
				findLines.addPoint((tempScan.back().get_x()/10) + 350, (tempScan.back().get_y()/10) + 350);
			tempScan.pop_back();
		}

		findLines.run();
		findLines.drawLines();
		tempScan.clear();
	}

	return 0;
}
