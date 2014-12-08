#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include "robot.h"
#include "pathPlanner.h"

#define FALSE	0
#define TRUE	1

using namespace std;
using namespace rw::sensor;
using namespace rw::loaders;

int main(int argc, char** argv) {
    std::string filename= "/Users/Anders/Documents/complete.pgm";
    std::cout << "loading image..." << std::endl;
    Image* img = PPMLoader::load(filename);

    cup_robot run(28, 1147, 4, img);
    run.make_wavefront(2404, 1318, 2858, 1324);
    run.findDiagonals();

    std::cout << "nr of v: " << run.queuePair.size() << std::endl;

    for (vector<coordinatesPair>::iterator vertex = run.queuePair.begin(); vertex != run.queuePair.end(); vertex++) {
        std::cout<<"vertex x: "<<vertex->x<<" y: " <<vertex->y<<" stops at x: "<< vertex->Xx<<" y:"<< vertex->Yy<<std::endl;
        run.move_to_vertex(vertex->x, vertex->y);
        run.cover_vertex(vertex->Xx, vertex->Yy);
    }


    std::cout << "last location x: " << run.get_current_x() << " y: " << run.get_current_y() << std::endl;
    std::cout << "number of steps: " << run.get_walked_pixels() << std::endl;
    std::cout << "number of cups collected: " << run.get_total_number_of_cups() << std::endl;
    std::cout << "\nsaving image..." << std::endl;
    // save image
    img->saveAsPGM("testout.pgm");

    // cleanup
    delete img;
}