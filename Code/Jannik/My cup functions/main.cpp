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

//void cover_vertex(Image *img, unsigned int vertex_x_value, unsigned int vertex_y_value);

int main(int argc, char** argv) {
    std::string filename= "testRoom0.pgm";
    //std::string filename= "complete_map_project.pgm";
    std::cout << "loading image..." << std::endl;
    Image* img = PPMLoader::load(filename);
    
    //cup_robot test(28, 1147, 4, img);
    cup_robot test(9, 16, 4, img);
    
    //test.make_wavefront(2404, 1318, 2858, 1324);
    test.make_wavefront(80,80);
    //test.print_wavefront_array();
    //test.findDiagonals();
    
    test.cover_vertex(26, 41);
    test.force_move_x_y(50, 16);
    test.cover_vertex(70, 16);
    
    /*
    std::cout << "nr of v: " << test.queuePair.size() << std::endl;
    
    int iter = 0;
    
    for (vector<coordinatesPair>::iterator vertex = test.queuePair.begin(); vertex != test.queuePair.end(); vertex++) {
        std::cout<<"vertex x: "<<vertex->x<<" y: " <<vertex->y<<" stops at x: "<< vertex->Xx<<" y:"<< vertex->Yy<<std::endl;
        if (iter==7) {
            break;
        }
        //test.move_to_vertex(vertex->x, vertex->y);
        //test.cover_vertex(vertex->Xx, vertex->Yy);
        //iter++;
        
        //test.print_wavefront_array();
    }
    */

    
   cout << "last location x: " << test.get_current_x() << " y: " << test.get_current_y() << endl;
   cout << "number of steps: " << test.get_walked_pixels() << endl;
   cout << "number of cups collected: " << test.get_total_number_of_cups() << endl;

    std::cout << "\nsaving image..." << std::endl;
    // save image
    img->saveAsPGM("testout.pgm");
    
    // cleanup
    delete img;
}