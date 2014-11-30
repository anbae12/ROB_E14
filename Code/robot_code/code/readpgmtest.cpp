#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include "robot.h"

#define FALSE	0
#define TRUE	1

using namespace std;
using namespace rw::sensor;
using namespace rw::loaders;

void cover_vertex(Image *img, unsigned int vertex_x_value, unsigned int vertex_y_value);

int main(int argc, char** argv) {
    std::string filename = "test.pgm";
    
    std::cout << "loading image..." << std::endl;
    Image* img = PPMLoader::load(filename);
    
    cout << "H:" << img->getHeight() << " W: " << img->getWidth() << endl;
    
    cup_robot test(10, 10, 4, img);
    
    cout << "x: " << test.get_current_x() << " y: " << test.get_current_y() << endl;


    
    test.make_wavefront(90, 17);
    test.follow_wavefront();
    //test.print_wavefront_array();
    //test.save_wavefront_to_map();
    test.return_from_wavefront();
    //test.findDiagonals(img, 0);
    
    cout << "last location x: " << test.get_current_x() << " y: " << test.get_current_y() << endl;
    cout << "number of steps: " << test.get_walked_pixels() << endl;
    
    std::cout << "saving image..." << std::endl;
    // save image
    img->saveAsPGM("testout.pgm");
        
    // cleanup
    delete img;
}





