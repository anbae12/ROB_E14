#include "convert.h"

/*****************************************************************************************
 *  Constructor. Loads the csv file and splits it into an array
 *****************************************************************************************/
csv_reader::csv_reader(std::string in_filename){
    load_file(in_filename);
}

/*****************************************************************************************
 *  Destructor
 *****************************************************************************************/
csv_reader::~csv_reader(){
    cleanup();
}

/*****************************************************************************************
 *  Returns the height / number of rows in the csv file/array
 *****************************************************************************************/
int csv_reader::get_height(){
    return height;
}

/*****************************************************************************************
 *  Returns the width / number of columns in the csv file/array
 *****************************************************************************************/
int csv_reader::get_width(){
    return width;
}

/*****************************************************************************************
 *  Returns the value of the array at index (x,y)
 *****************************************************************************************/
int csv_reader::get_array_at(int x, int y){
    return stoi(string_array[y][x]);
}

/*****************************************************************************************
 *  Loads a csv file and splits it into an array
 *****************************************************************************************/
void csv_reader::load_file(string in_filename){
    filename = in_filename;
    cout << "Loading " << filename << "..." << endl;
    ifstream input_csv(filename);
    
    string temp_csv_string((std::istreambuf_iterator<char>(input_csv)), std::istreambuf_iterator<char>());
    csv_string = temp_csv_string;
    
    split_string_into_array(csv_string, ";", "\n");
    cout << "H: " << height << " W: " << width << endl;
    
    //print_array();
    
    //cleanup();
}

/*****************************************************************************************
 *  Saves the array to a .txt file
 *****************************************************************************************/
void csv_reader::save_array_to_file(){
    
    ofstream output_file(filename + "_array.txt");
    
    if (output_file.is_open())
    {
        output_file << csv_string;
        output_file.close();
    }
    else cout << "Unable to open file";
}

/*****************************************************************************************
 *  Prints the string obtained from the unaltered .csv file
 *****************************************************************************************/
void csv_reader::print_string() {
    cout << "\n\n" << csv_string << "\n\n";
}

/*****************************************************************************************
 *  Returns the value number of occurences of the search string that occure before
 *  the stop string. If no stop string is specified, it searches the entire length.
 *****************************************************************************************/
int csv_reader::number_of_occurences(string &target_str, string start_str, string stop_str){
    int number_of_items_found = 0;
    size_t keyword_start = 0;
    size_t keyword_stop = 0;
    
    //if no stop string is specified search entire file
    if (stop_str == "") {
        keyword_start = target_str.find(start_str, 0);
        //find last element of the type
        keyword_stop = target_str.rfind(start_str);
    }
    else if (stop_str == ""&&start_str == "") {
        number_of_items_found = (int)target_str.length();
        //skip while loop
        keyword_start = keyword_stop++;
    }
    else {
        keyword_start = target_str.find(start_str, 0);
        keyword_stop = target_str.find(stop_str, 0);
    }
    
    while ((keyword_start<keyword_stop) && (keyword_start != string::npos)){
        keyword_start = target_str.find(start_str, keyword_start);
        number_of_items_found++;
        keyword_start++;
    }
    
    return number_of_items_found;
    
}

/*****************************************************************************************
 *  Splits the string into an array where, height = nr. rows and width = nr. columns
 *****************************************************************************************/
void csv_reader::split_string_into_array(string &target_str, string delimiter_1, string delimiter_2){
    
    size_t keyword_start;
    size_t keyword_stop;
    size_t keyword_linebreak;
    
    width = number_of_occurences(csv_string, ";", "\n");
    height = number_of_occurences(csv_string, "\n", "");    //last row won't have a newline
    
    //if no newline is found the file is probably using return instead
    if (!width) {
        width = number_of_occurences(csv_string, ";", "\r");
        height = number_of_occurences(csv_string, "\r", "");    //last row won't have a newline
    }
    
    //cout << "w: " << width << " h: " << height << endl;
    
    //create dynamic array the size of the picture
    string_array = new string*[height];
    for (int row = 0; row<height; row++) {
        string_array[row] = new string[width];
    }
    
    //find delimiter 1
    keyword_start = -1;
    //find next occurence of delimiter 1 after delimiter 1
    keyword_stop = target_str.find(delimiter_1, 0);
    //find linebreak
    keyword_linebreak = target_str.find(delimiter_2, 0);
    
    for (int row = 0; row<height; row++) {
        for (int col = 0; col<width; col++) {
            // if linebreak comes before ','
            if (keyword_linebreak<keyword_stop) {
                string_array[row][col] = target_str.substr(keyword_start + 1, keyword_linebreak - keyword_start - delimiter_2.length()-1);
                
                keyword_start = keyword_linebreak;
                keyword_stop = target_str.find(delimiter_1, keyword_start + 1);
                keyword_linebreak = target_str.find(delimiter_2, keyword_stop);
                
            }
            else {
                string_array[row][col] = target_str.substr(keyword_start + 1, keyword_stop - keyword_start - delimiter_1.length());
                keyword_start = target_str.find(delimiter_1, keyword_start + 1);
                keyword_stop = target_str.find(delimiter_1, keyword_start + 1);
            }
        }
    }
}

/*****************************************************************************************
 *  Prints the array
 *****************************************************************************************/
void csv_reader::print_array(){
    // print array
    for (int row = 0; row<height; row++) {
        for (int col = 0; col<width; col++) {
            cout << string_array[row][col] << "\t";
        }
        cout << endl;
    }
}

/*****************************************************************************************
 *  Converts the array into a string
 *****************************************************************************************/
void csv_reader::convert_array_to_string(string &target_str, string **ptr) {
    
    target_str.clear();
    
    for (int row = 0; row<height; row++) {
        for (int col = 0; col<width; col++) {
            
            if (col<width - 1) {
                target_str += string_array[row][col] + "&\t";
            }
            else {
                target_str += string_array[row][col];
            }
        }
        target_str += "\n";
    }
}

/*****************************************************************************************
 *  Deallocates the dynamic array.
 *****************************************************************************************/
void csv_reader::cleanup(){
    
    // deallocate memory to prevent memory leak
    for (int i = 0; i < height; ++i) {
        delete[] string_array[i];
        string_array[i] = nullptr;
    }
    delete[] string_array;
    string_array = nullptr;
}

