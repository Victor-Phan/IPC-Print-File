#include <stdio.h>
#include <string.h>
#include <iostream>
#include "client.hpp"
#include "message.hpp"
#include "server.hpp"

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
            service = new Client();
            (dynamic_cast<Client*>(service))->connectClient(filename,priority);
        } catch (...) {
            printMessage("Please enter a number between 1 and 10 for priority");
            return -1;
        }
    } else {
        printMessage("Please provide arguments [client/server] [filename] [priority]");
        return -1;
    }
    delete service;
    return 0;
}