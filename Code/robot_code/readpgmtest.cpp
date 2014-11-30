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

void cover_vertex(Image *img, unsigned int vertex_x_value, unsigned int vertex_y_value);

int main(int argc, char** argv) {
    std::string filename= "/Users/Anders/Documents/test.pgm";
    
    std::cout << "loading image..." << std::endl;
    Image* img = PPMLoader::load(filename);
    
    cout << "H:" << img->getHeight() << " W: " << img->getWidth() << endl;
    
    cup_robot test(3,3, 4, img);
    
    //cout << "x: " << test.get_current_x() << " y: " << test.get_current_y() << endl;
    
    
    test.make_wavefront(111, 42);
    //test.follow_wavefront();
    //test.print_wavefront_array();
    test.save_wavefront_to_map();
    //test.return_from_wavefront();
    pathPlanner ppp;
    
    test.findDiagonals();
    
    
    
    for (vector<coordinatesPair>::iterator vertex = test.queuePair.begin(); vertex != test.queuePair.end(); vertex++) {
        std::cout<<vertex->x<<"," <<vertex->y<<" ; "<< vertex->Xx<<","<< vertex->Yy<<std::endl;
        ppp.addVertex(vertex->x, vertex->y, vertex->Xx, vertex->Yy);
    }
    ppp.getPath();
    
    // cout << "last location x: " << test.get_current_x() << " y: " << test.get_current_y() << endl;
    // cout << "number of steps: " << test.get_walked_pixels() << endl;
    
    std::cout << "\nsaving image..." << std::endl;
    // save image
    img->saveAsPGM("testout.pgm");
    
    // cleanup
    delete img;
}





