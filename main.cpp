#include <stdio.h>
#include <string.h>
#include <iostream>
#include "client.hpp"
#include "message.hpp"
#include "server.hpp"
/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: 	main.cpp - The main driver of the program
--
--
-- PROGRAM: 		Message Queue Application
--
-- FUNCTIONS:
--                  int main(int argc, char* argv[])
--                      -entry point into the program
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
--                  Takes in command line arguments to start a server or connect a client.
--                  Ex arguments:
--                              ./executable server
--                              ./executable client filename.txt 4080
--------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
    Service* service = nullptr;
    if (argc == 2 && !strcmp(argv[1], "server")) {
        //create server and print id
        service = new Server();
        (dynamic_cast<Server*>(service))->startServer();
    } else if (argc == 4 && !strcmp(argv[1], "client")) {
        //Check params
        try {
            // send to server
            char * filename = argv[2];
            int priority = atoi(argv[3]);
            if(priority < 1 || priority > MAXMESSAGEDATA) {
                std::string msg = "Priority must be below ";
                msg += std::to_string(MAXMESSAGEDATA) + " and not negative";
                printMessage(msg);
                return -1;
            }
            service = new Client();
            (dynamic_cast<Client*>(service))->connectClient(filename,priority);
        } catch (...) {
            std::string msg = "Please enter a number between 1 and ";
            msg += std::to_string(MAXMESSAGEDATA) + " for priority";
            printMessage(msg);
            return -1;
        }
    } else {
        printMessage("Please provide arguments [client/server] [filename] [priority]");
        return -1;
    }
    delete service;
    return 0;
}