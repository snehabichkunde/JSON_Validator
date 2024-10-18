#include <iostream>
#include <stack>
#include <regex>
#include "../include/error_dectection.h"

// Function to detect errors in the JSON content
bool detectErrors(const std::string& jsonContent) {
    bool hasError = false;

    if (checkBrackets(jsonContent)) {
        hasError = true;
    }
    if (checkCommas(jsonContent)) {
        hasError = true;
    }
    if (checkKeyValuePair(jsonContent)) {
        hasError = true;
    }
    return hasError;
}

// Function to check for bracket mismatches
bool checkBrackets(const std::string& jsonContent) {
    std::stack<char> st;
    for (int i = 0; i < jsonContent.size(); ++i) {
        char ch = jsonContent[i];
        if (ch == '{' || ch == '[') {
            st.push(ch);
        } else if (ch == '}' || ch == ']') {
            if (st.empty()) {
                std::cerr << "Error: Unmatched closing bracket." << std::endl;
                return true;
            }
            if ((ch == '}' && st.top() != '{') || (ch == ']' && st.top() != '[')) {
                std::cerr << "Error: Mismatched brackets." << std::endl;
                return true;
            } else {
                st.pop();
            }
        }
    }
    if (!st.empty()) {
        std::cerr << "Error: Unmatched opening bracket." << std::endl;
        return true;
    }
    return false;
}

// Function to check key-value pairs
bool checkKeyValuePair(const std::string& jsonContent) {
    int i = 0;
    while (i < jsonContent.size() && std::isspace(jsonContent[i])) {
        i++;
    }

    if (jsonContent[i] != '{') {
        std::cerr << "Error: Opening Bracket is missing." << std::endl;
        return true;
    }

    i++;  // Move past opening bracket

    while (i < jsonContent.size()) {

        if (jsonContent[i] == '}') {
            i++;
            continue;
        }

        while (i < jsonContent.size() && std::isspace(jsonContent[i])) {
            i++;
        }

        if (jsonContent[i] != '\"') {
            std::cerr << "Syntax Error: Key must be enclosed in quotes." << std::endl;
            return true;
        }

        i++;
        std::string key = "";
        while (i < jsonContent.size() && jsonContent[i] != '\"') {
            key += jsonContent[i];
            i++;
        }

        if (jsonContent[i] != '\"') {
            std::cerr << "Error: Missing closing quote in key." << std::endl;
            return true;
        }

        i++;  // Move past closing quote

        if (!validKey(key)) {
            std::cerr << "Error: Invalid Key: \"" << key << "\"" << std::endl;
            return true;
        }

        while (i < jsonContent.size() && std::isspace(jsonContent[i])) {
            i++;
        }

        if (jsonContent[i] != ':') {
            std::cerr << "Syntax Error: Missing colon (:) after key." << std::endl;
            return true;
        }

        i++;  // Move past colon

        while (i < jsonContent.size() && std::isspace(jsonContent[i])) {
            i++;
        }

        if (jsonContent[i] == '{') {
            std::string nestedObject = "";
            nestedObject+= jsonContent[i];
            int braceCount = 1;
            i++;
            while (i < jsonContent.size() && braceCount > 0) {
                if (jsonContent[i] == '{') braceCount++;
                if (jsonContent[i] == '}') braceCount--;
                nestedObject += jsonContent[i];
                i++;
            }

            if (braceCount != 0) {
                std::cerr << "Error: Unmatched brackets in nested object." << std::endl;
                return true;
            }

            if (!checkValidObject(nestedObject)) {
                std::cerr << "Invalid object: " << nestedObject << std::endl;
                return true;
            }
        } else if (jsonContent[i] == '\"') {
            i++;  // Move past the opening quote
            std::string str = "";
            while (i < jsonContent.size() && jsonContent[i] != '\"') {
                str += jsonContent[i];
                i++;
            }

            if (jsonContent[i] != '\"') {
                std::cerr << "Error: Missing closing quote in value." << std::endl;
                return true;
            }

            i++;  // Move past the closing quote
        }
        // if the value is number 
        else if(std::isdigit(jsonContent[i]) || (jsonContent[i] == '-' && std::isdigit(jsonContent[i + 1]))){
            std:: string number = "";
            if(jsonContent[i] == '-'){
                number+= jsonContent[i];
                i++;
            }
            while(i < jsonContent.size() && std::isdigit(jsonContent[i]))
            {
                number+= jsonContent[i];
                i++;
            }
            if(jsonContent[i]=='.' && i < jsonContent.size()){
                number+= jsonContent[i];
                i++;
            }
            while(i < jsonContent.size() && std::isdigit(jsonContent[i]))
            {
                number+= jsonContent[i];
                i++;
            }
            if(!checkValidNumber(number)){
                std::cerr << "Error: Invalid number value: " << number << std::endl;
                return true;
            }
        }
        // if the key is bool or NULL
        else if(i+4 < jsonContent.size() && (jsonContent.substr(i, 4)=="true" || jsonContent.substr(i, 4)=="null") ){
            i+=4;
        }
        else if(i+5 < jsonContent.size() && jsonContent.substr(i, 5)=="false"){
            i+=5;
        }

        else if(jsonContent[i]=='['){
            std::string array = "";
            array += jsonContent[i];
            i++;
            while (i < jsonContent.size() && std::isspace(jsonContent[i])){
                i++;
            }
            while(i<jsonContent.size() && jsonContent[i]!= ']'){
                array += jsonContent[i];
                i++;
            }
            array += jsonContent[i];
            if(i==jsonContent.size()){
                std:: cerr << "Error: Arrya beacket is not closed" << std::endl;
                return true;
            }
            if (!checkValidArray(array, i)) {
                std::cerr << "Error: Invalid Array" << std::endl;
                return true;
        }

            i++;
        }


        while (i < jsonContent.size() && std::isspace(jsonContent[i])) {
            i++;
        }
        

        if (jsonContent[i] == ',') {
            i++;
        } else if (jsonContent[i] == '}') {
            i++;
        } else {
            std::cerr << "Error: Unexpected token after value." << std::endl;
            return true;
        }
    }

    return false;
}

// Function to validate a key
bool validKey(const std::string& key) {
    for (char ch : key) {
        if (ch == '\"' || ch == '\n' || ch == '\r' || ch == '\t') {
            std::cerr << "Error: Invalid character in key: \"" << key << "\"" << std::endl;
            return false;
        }
    }
    return true;
}

// Function to check the validity of a nested object
bool checkValidObject(const std::string& object) {
    if(object.empty()){
        return true;
    }
    if (detectErrors(object)) {
        return false;
    }
    return true;
}

bool checkValidNumber(const std::string &number)
{
    // This can be improved based on specific needs
    std::regex numberRegex("^-?\\d+(\\.\\d+)?$");
    return std::regex_match(number, numberRegex);
}


bool checkValidArray(const std::string &array, int &i) {
    // Check if array starts and ends with correct brackets
    if (array[i] != '[') {
        std::cerr << "Error: Array must start with '['." << std::endl;
        return false;
    }

    i++; // Skip the opening bracket

    // Loop through the array elements
    while (i < array.size()) {
        // Skip whitespace
        while (i < array.size() && std::isspace(array[i])) i++;

        // Check for array closing bracket
        if (array[i] == ']') {
            i++; // Move past closing bracket
            return true; // Valid array
        }

        // Parse string elements in the array
        if (array[i] == '"') {
            i++; // Move past the opening quote
            while (i < array.size() && array[i] != '"') {
                i++;
            }

            // If we reached the end without finding a closing quote, it's an error
            if (i == array.size() || array[i] != '"') {
                std::cerr << "Error: String in array is not properly closed." << std::endl;
                return false;
            }
            i++; // Move past the closing quote
        } 
        // Parse numbers
        else if (std::isdigit(array[i]) || array[i] == '-') {
            while (i < array.size() && (std::isdigit(array[i]) || array[i] == '.')) {
                i++;
            }
        } 
        // Parse booleans and null
        else if (array.substr(i, 4) == "true" || array.substr(i, 4) == "null") {
            i += 4; // Move past "true" or "null"
        } else if (array.substr(i, 5) == "false") {
            i += 5; // Move past "false"
        } 
        // Handle nested arrays
        else if (array[i] == '[') {
            if (!checkValidArray(array, i)) {
                return false; // If nested array is invalid, return error
            }
        } 
        // Handle unexpected characters
        else {
            std::cerr << "Error: Invalid element in array." << std::endl;
            return false;
        }

        // Skip whitespace and check for commas
        while (i < array.size() && std::isspace(array[i])) i++;
        if (i < array.size() && array[i] == ',') {
            i++; // Move past the comma
        } else if (array[i] != ']' && i < array.size()) {
            std::cerr << "Error: Array element must be followed by a comma or closing bracket." << std::endl;
            return false;
        }
    }

    std::cerr << "Error: Array bracket is not closed." << std::endl;
    return false;
}



// Function to check for comma-related issues (you can implement further logic here)
// bool checkCommas(const std::string& jsonContent) {
//     // Implement logic for detecting trailing commas, missing commas, etc.
//     return false;
// }
