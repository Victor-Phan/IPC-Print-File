/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: 	client.cpp - This file contains the logic to connect the client to the message queue, request
--                               the file from the server, and read messages on the queue that contains the 
--                               file contents
--
--
-- PROGRAM: 		Message Queue Application
--
-- FUNCTIONS:
--                  bool connectClient(char* filename, int priority)
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
--                  Client class contains the ability to create a client. It will open the queue in order to send a message
--                  to the server.
--
--------------------------------------------------------------------------------------------------------------------*/
#include "client.hpp"

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	connectClient
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 	Victor Phan
--
-- PROGRAMMER: 	Victor Phan
--
-- INTERFACE:	bool connectClient(char* filename, int priority)
--                  filename - the file name that is the client is requesting from the server
--                  priority - the priority that the client will receive the file contents at
--                             higher priority means faster transfer
--
-- RETURNS:     Returns true when the entire file is received from the server. Returns false in all other cases.
--
-- NOTES:
--              Opens the message queue. Then, sends the the requested filename to the server.
--              Waits for response from the server and prints out data or a error message.
--
-------------------------------------------------------------------------------------------------------------------*/
bool Client::connectClient(char* filename, int priority) {
    lpid = (long)getpid();
    running = true;
    Message file_msg;
    file_msg.msg_type = SERVER_MSG_TYPE;
    file_msg.priority = priority;
    file_msg.file_name = true;
    strcpy(file_msg.msg_data, filename);
    file_msg.msg_len = strlen(filename);
    file_msg.from_process = lpid;
    if (open_queue() == -1) {
        return false;
    }
    if (send_message(&file_msg) == -1) {
        printMessage("Error Sending.");
        return false;
    }

    while (running) {
        Message recv;
        if (read_message(lpid, &recv) == -1) {
            //process message
            std::cout << "Data: ";
            printMessage(recv.msg_data);
            return false;
        }
        //create thread to print message to screen?..
        //will need to synchronize these threads in order to (mutex?)
        // print in the correct order
        if (recv.last_message) {
            printMessage("Received entire file..");
            return true;
        } else if (recv.msg_len == 0) {
            printMessage("File does not exist on server.");
            return false;
        } else {
            printMessage(recv.msg_data, false);
        }
    }
    return false;
}

