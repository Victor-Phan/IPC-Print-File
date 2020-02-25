#include "filehandler.hpp"
bool fileExists(const std::string& name) {
    printMessage(name);
    printMessage("File opening..");
    if (FILE *file = fopen(name.c_str(), "r")) {
        printMessage("File exist");
        fclose(file);
        return true;
    } else {
        printMessage("Failure opening file.");
        return false;
    }   
}