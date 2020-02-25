#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "server.hpp"
#include "client.hpp"
#include "message.hpp"

int main(int argc, char *argv[])
{
    Service* service = nullptr;
    if (argc == 2 && !strcmp(argv[1], "server")) {
        //create server and print id 
        service = new Server();
        (static_cast<Server*>(service))->startServer();
    }else if(argc == 4 && !strcmp(argv[1], "client")) {
        //Check params
        
        // send to server
        service = new Client();
        (static_cast<Client*>(service))->connectClient();
    } else {
        printMessage("Please provide arguments [client/server] [filename] [priority]");
        return -1;
    }
    delete service;
    return 0;
}