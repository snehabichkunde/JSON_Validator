#include<iostream>
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
    if(checkQuotes(jsonContent)){
        hasError = true;
    }
    return hasError;
}

bool checkBrackets(const std::string& jsonContent)
{
    std:: stack<char>st;
    for(size_t i = 0; i < jsonContent.size(); ++i){
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

bool checkQuotes(const std::string& jsonContent){
    // need to write logic here 

    return false;
}

bool checkCommas(const std::string& jsonContent){
    // need to write logic here 


    return false;
}