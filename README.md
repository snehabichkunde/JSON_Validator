# JSON Syntax Validator in C++

## Project Overview
This project is a C++ program that takes a JSON file as input, reads its content, and detects any syntax errors. If a syntax error is found, the program reports the error and specifies the line number where the error occurs. 

The goal of this project is to help users identify issues in their JSON files and understand where they went wrong, making debugging easier.

## Features
- Reads JSON files from a given file path.
- Detects common syntax errors such as missing brackets, commas, or incorrect data types.
- Reports the line number and description of the detected syntax error.
- Displays a success message if the JSON file is valid.

## How It Works
1. **Pass the JSON file path as a command-line argument**: The program reads the file from the specified path.
2. **Parse the file**: It parses the JSON content and checks for syntax errors.
3. **Report errors**: If errors are detected, the program outputs the line number and type of error.
4. **Valid JSON**: If no errors are found, the program reports that the JSON is valid.


