#include<iostream>
#include "../include/file_reader.h"

int main(int argc, char* argv[])
{
    if(argc<2){
        std::cerr << "Error: Please provide a file paths an argument." << std:: endl;
        return 1; // indicating the errors 
    }
    // get file path from the argument 
    std:: string filePath = argv[1];
    
    // send filePath to read the file content 
    std:: string content = readFile(filePath);

    if(content.empty()){
        std:: cerr << "Error: Could not read the file" << std:: endl;
        return 1;
    }

    return 0;
}