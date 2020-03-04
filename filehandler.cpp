/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: 	filehandler.cpp - This file contains the logic to check if a file exists and reads from it.
--
--
-- PROGRAM: 		Message Queue Application
--
-- FUNCTIONS:
--                  bool fileExists(const std::string& name)
--                  std::string readFile(int bytes)
--
-- DATE: 			February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 		Victor Phan
--
-- PROGRAMMER: 		Victor Phan
--
-- NOTES:
--                  FileHandler class pertains logic dealing with primarily text files.
--------------------------------------------------------------------------------------------------------------------*/

#include <cstring>
#include "filehandler.hpp"

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	fileExists
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 	Victor Phan
--
-- PROGRAMMER: 	Victor Phan
--
-- INTERFACE:	bool fileExists(const std::string& name)
--                  name - the filename path that is checked for existing
--
-- RETURNS:     Returns true if the file exists.
--
-- NOTES:
--              Opens the file and closes it in order to check if the specified file exists.
--
-------------------------------------------------------------------------------------------------------------------*/
bool FileHandler::fileExists(const std::string& name) {
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

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	readFile
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 	Victor Phan
--
-- PROGRAMMER: 	Victor Phan
--
-- INTERFACE:	std::string readFile(int bytes)
--                  bytes - the number of bytes to rad from the file
--
-- RETURNS:     Returns the data that was read. returns empty string if no data was read.
--
-- NOTES:
--              Opens the file and reads n bytes from the file. Then closes the file
--
-------------------------------------------------------------------------------------------------------------------*/
std::string FileHandler::readFile(int bytes) {
    //Default message
    char buffer[bytes];
    std::string data;
    int startFilePointer = readPointer;
    memset(buffer,0,bytes);
    FILE *file = fopen(filename.c_str(), "r");
    fseek(file,readPointer,SEEK_SET);
    if(!feof(file)) {
        readPointer += fread(buffer, 1, sizeof(buffer), file);
        data.append(buffer,bytes);
    }

    fclose(file);
    if(startFilePointer == readPointer) {
        return "";
    }
    return data;
}

