#pragma once
#include <iostream>
#include "message.hpp"

class FileHandler {
protected:
    std::string filename;
    int readPointer = 0;
public:
    //Must be valid file
    FileHandler(const std::string& name) : filename(name){}
    static bool fileExists(const std::string& name);
    std::string readFile(int bytes);
};