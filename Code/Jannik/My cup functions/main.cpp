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
    std::string filename= "largeRoom.pgm";
    std::cout << "loading image..." << std::endl;
    Image* img = PPMLoader::load(filename);
    
    cup_robot test(9, 9, 4, img);
    
    test.make_wavefront(233, 191);
    
    pathPlanner ppp;

    test.findDiagonals();
/*
    for (vector<coordinatesPair>::iterator vertex = test.queuePair.begin(); vertex != test.queuePair.end(); vertex++) {
   //     std::cout<<vertex->x<<"," <<vertex->y<<" ; "<< vertex->Xx<<","<< vertex->Yy<<std::endl;
        ppp.addVertex(vertex->x, vertex->y, vertex->Xx, vertex->Yy);
    }
    ppp.getPath();

    cout << ppp.path.size() <<endl;
    
    
//    DENNE HER VIRKER! Dog er der fejl.. tjek linje 56-74
    while (!ppp.path.empty()) {
        cout << "topx: " << ppp.vertices[ppp.path.front()].top.x << " topy: " << ppp.vertices[ppp.path.front()].top.y << endl;
        cout << "botx: " << ppp.vertices[ppp.path.front()].bottom.x << " boty: " << ppp.vertices[ppp.path.front()].bottom.y << endl;
      
        if (ppp.vertices[ppp.path.front()].bottom.x==75 && ppp.vertices[ppp.path.front()].bottom.y==51) {
            test.cover_vertex(75 ,50 );
        } else
            test.cover_vertex(ppp.vertices[ppp.path.front()].bottom.x ,ppp.vertices[ppp.path.front()].bottom.y );
        
        ppp.path.pop_front();
        //test.force_move_x_y(ppp.vertices[ppp.path.front()].top.x, ppp.vertices[ppp.path.front()].top.y);
        test.move_in_straight_line(ppp.vertices[ppp.path.front()].top.x, ppp.vertices[ppp.path.front()].top.y);
   }
 
    //test.cover_vertex(65, 65);
    
    */
    
   cout << "last location x: " << test.get_current_x() << " y: " << test.get_current_y() << endl;
   // cout << "number of steps: " << test.get_walked_pixels() << endl;
    
    std::cout << "\nsaving image..." << std::endl;
    // save image
    //img->saveAsPGM("testout.pgm");
    
    // cleanup
    delete img;
}