#include <iostream>
#include </Users/jannikgade/Dropbox/ROBTEK/ROB5/ROB5/kalman_example/KalmanExample/laser_range_scanner.h> // change to the correct folder
#include "/Users/jannikgade/Dropbox/ROBTEK/ROB5/ROB5/kalman_example/KalmanExample/pixel.h" // change to the correct folder

int main(int argc, char *argv[])
{
    laser_range_scanner test("longrun_2.csv");
    
    std::vector<pixel> temp_vector;
    
    temp_vector = test.scan();
    
    while (!temp_vector.empty()) {
        std::cout << temp_vector.back().get_x() << "," << temp_vector.back().get_y() << std::endl;
        temp_vector.pop_back();
    }
     
    /*
    
    for(int i=0;i<circlePoints.size();i++){
        int x = circlePoints[i].x()*scale + x_offset;
        int y = circlePoints[i].y()*scale + y_offset;
        img.setPixel16U(x, y, 0);
        //cout << "x: " << x << " y: " << y << endl;
        
        if (!(i%682)) {
            if (counter<100000)
                zeros = "";
            if (counter<10000)
                zeros = "0";
            if (counter<1000)
                zeros = "00";
            if (counter<100)
                zeros = "000";
            if (counter<10)
                zeros = "0000";
            string filen = "pics_for_vid/scanner" + zeros + to_string(counter) + ".pgm";
            img.saveAsPGMAscii(filen);
            counter++;
            for(int x=0;x<img.getWidth();x++)
                for(int y=0;y<img.getWidth();y++)
                    img.setPixel16U(x,y,65000);
        }
        
    }
     */

    //img.saveAsPGMAscii("test.pgm");
    return 0;
}

