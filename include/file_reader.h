#ifndef FILE_READER_H
#define FILE_READER_H
// if not defined FILE_READER_H yet define FILE_READER_H

#include <string>
#include <fstream>
#include <iostream>

// Function to read the content of a file and return it as a string
std::string readFile(const std::string& filePath);

#endif // FILE_READER_H
/*
The #endif at the end closes the conditional and ensures 
that the content between #ifndef and #endif is only included once per compilation unit
*/