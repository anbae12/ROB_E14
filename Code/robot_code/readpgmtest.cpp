#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include "robot.h"
#include "findPoints"

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
    
    // place a cup at the location
    //test.color_pixel(43, 14, 150);
    //test.color_pixel(45, 10, 150);
    
    //test.collect_cup(55, 13);
    
    cout << "x: " << test.get_current_x() << " y: " << test.get_current_y() << endl;
    //test.cover_vertex(110,22);
    //test.cup_scanner();
    
    //cout << "x: " << test.get_current_x() << " y: " << test.get_current_y() << endl;
    //cout << "number of steps: " << test.get_walked_pixels() << endl;
    //cout << "cups collected: " << test.get_total_number_of_cups() << endl;
    
    test.make_wavefront(90, 17);
    //test.follow_wavefront();
    //test.print_wavefront_array();
    test.save_wavefront_to_map();
    //test.return_from_wavefront();
    
    findPoints fp;
    fp.findDiagonals(img,channel);
    
    
    
    
    
    cout << "last location x: " << test.get_current_x() << " y: " << test.get_current_y() << endl;
    cout << "number of steps: " << test.get_walked_pixels() << endl;
    
    std::cout << "saving image..." << std::endl;
    // save image
    img->saveAsPGM("testout.pgm");
        
    // cleanup
    delete img;
}





