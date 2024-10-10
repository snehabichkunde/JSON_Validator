#include "../include/file_reader.h"


std:: string readFile(const std:: string& filePath)
{
    std:: ifstream file(filePath); // open the file 
    if(!file.is_open()){ // check if the file is open 
        std:: cerr << "Error: Could not open the file" << std::endl;
        return "";
    }
    // read the file content into string s
    std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    
    file.close();  // close the file after reading 
    return content;  // return the content of the file 
}