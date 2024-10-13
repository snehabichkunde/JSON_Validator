#include<iostream>
#include <regex>
#include "../include/error_dectection.h"

bool detectErrors(const std:: string& jsonContent)
{
    bool hasError = false;

    if(checkBrackets(jsonContent)){
        hasError = true;
    }
    if(checkCommas(jsonContent)){
        hasError = true;
    }
    if(checkKeyValuePair(jsonContent)){
        hasError = true;
    }
    return hasError;
}

bool checkBrackets(const std::string& jsonContent)
{
    std:: stack<char>st;
    for(int i = 0; i < jsonContent.size(); ++i){
        char ch = jsonContent[i];
        if(ch == '{' || ch == '['){
            st.push(ch);
        }
        else if(ch == '}'|| ch == ']'){
            if(st.empty()){
                std::cerr << "Error: Unmatched closing bracket." << std::endl;
                return true;
            }
            else if((ch=='}' && st.top() !='{')||(ch == ']'&&st.top()!='[')){
                std::cerr << "Error: Mismatched brackets." << std::endl;
                return true;
            }
            else{
                st.pop();
            }
        }
    }
    if(st.empty()){
        return false;
    }
    std::cerr << "Error: Unmatched opening bracket." << std::endl;
    return true;
}

bool checkKeyValuePair(const std::string& jsonContent) {
    if (jsonContent[0] != '{') {
        std::cerr << "Error: Opening Bracket is missing" << std::endl;
        return true;
    }
    if (jsonContent[jsonContent.size() - 1] != '}') {
        std::cerr << "Error: Closing Bracket is missing" << std::endl;
        return true;
    }

    int i = 1;
    while (i < jsonContent.size() - 1) {
        // Skip whitespace
        while (i < jsonContent.size() - 1 && std::isspace(jsonContent[i])) {
            i++;
        }

        // Extract key
        if (jsonContent[i] != '\"') {
            std::cerr << "Syntax Error: Key must be enclosed in quotes." << std::endl;
            return true;
        }
        i++;

        std::string key;
        while (jsonContent[i] != '\"' && i < jsonContent.size() - 1) {
            key += jsonContent[i];
            i++;
        }

        if (jsonContent[i] != '\"') {
            std::cerr << "Syntax Error: Key must be enclosed in quotes." << std::endl;
            return true;
        }

        // Validate key
        if (!validKey(key)) {
            std::cerr << "Error: Invalid Key: \"" << key << "\"" << std::endl;
            return true;
        }

        i++; // Move past closing quote

        // Check for colon
        while (i < jsonContent.size() - 1 && std::isspace(jsonContent[i])) {
            i++;
        }
        if (jsonContent[i] != ':') {
            std::cerr << "Syntax Error: Missing colon (:) after key." << std::endl;
            return true;
        }
        i++; // Move past colon

        // Skip whitespace for value
        while (i < jsonContent.size() - 1 && std::isspace(jsonContent[i])) {
            i++;
        }
        
        // Implement logic to check for valid value
        // ...
        // value can be array, string , number , object 
        // lets check for the object 
        if(jsonContent[i] == '{') {
            std::string obj = "";
            while(jsonContent[i] != '}') {
                obj += jsonContent[i];
                i++;
            }
            obj += jsonContent[i]; // include closing '}'
            i++; // Move past the closing brace

            if(!checkValidObject(obj)) {
            std::cerr << "Invalid object: " << obj << std::endl;
            return true;
        }
}


        // Skip to next key-value pair
        while (i < jsonContent.size() - 1 && jsonContent[i] != ',') {
            i++;
        }
        if (jsonContent[i] == ',') {
            i++; // Move past comma for the next iteration
        }
    }

    return false;
}



bool validKey(const std::string& key) {

    // Initialize a counter for escape sequences
    bool isEscaped = false;

    // Iterate through the key excluding the surrounding quotes
    for (int i = 1; i < key.length() - 1; ++i) {
        char ch = key[i];

        // Check for escape character
        if (ch == '\\') {
            isEscaped = !isEscaped; // Toggle the escaped state
            continue;
        }

        // If not escaped, check for invalid characters
        if (!isEscaped && (ch == '\"' || ch == '\n' || ch == '\r' || ch == '\t')) {
            std::cerr << "Error: Invalid character in key: \"" << key << "\"" << std::endl;
            return false;
        }

        // Reset the escape state after processing a valid character
        isEscaped = false;
    }

    // If we reach here, the key is valid
    return true;
}

bool checkValidObject(const std::string &object)
{
    if(detectErrors(object)){
        //std::cout << "Hey" << std:: endl;
        return false;
    }
    return true;
}



bool checkCommas(const std::string& jsonContent){
    // need to write logic here 
    return false;
}