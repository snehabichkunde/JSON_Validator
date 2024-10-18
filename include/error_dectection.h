/* check if there are any synatax error are there like 
    missing brackets 
    missing commas
    unclosed string  
*/

#ifndef ERROR_DETECTION_H
#define ERROR_DETECTION_H

#include<string>
#include<stack>

bool detectErrors(const std::string& jsonContent);

bool checkBrackets(const std::string& jsonContent);
bool checkKeyValuePair(const std::string& jsonContent);
bool checkCommas(const std::string& jsonContent);
bool validKey(const std:: string& key);
bool checkValidObject(const std::string &object);
bool checkValidNumber(const std::string &number);
bool checkValidArray(const std::string &array, int &i);

#endif // ERROR_DETECTION_H