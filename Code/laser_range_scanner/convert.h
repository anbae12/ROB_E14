//
//  convert.h
//  laser_range_scanner
//
//  Created by Jannik Gade on 01/12/14.
//
//

#ifndef __laser_range_scanner__convert__
#define __laser_range_scanner__convert__

#include <iostream>
#include <fstream>
#include <string>



class csv_reader {
protected:
    int width;
    int height;
    std::string **string_array;         //array pointer
    std::string filename;
    std::string csv_string;      //holds string version of csv file
    
    void save_array_to_file(void);
    
    void split_string_into_array(std::string &target_str, std::string delimiter_1, std::string delimeter_2);
    int number_of_occurences(std::string &target_str, std::string start_str, std::string stop_str="");
    
    void convert_array_to_string(std::string &target_str, std::string **ptr);
    void cleanup();
public:
    csv_reader(std::string in_filename);
    ~csv_reader();
    void load_file(std::string in_filename);
    void print_array();
    void print_string();
    int get_height();
    int get_width();
    int get_array_at(int x, int y);
};

#endif
