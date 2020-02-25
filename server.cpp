#include "server.hpp"

bool Server::startServer() {
    running = true;
    if (open_queue() == -1) {
        return false;
    }
    while (running) {
        Message message;
        if (read_message(SERVER_MSG_TYPE, &message) == -1) {
            printMessage("Failed to read initial message");
            return false;
        }

        switch (pid = fork()) {
            case -1:
                printMessage("Error creating process");
                break;
            case 0:  //Child process
                     //handle processing of client
                     //pass by value so that there is no seg fault
                std::cout << "Msg Type: ";
                printMessage(message.msg_type);
                std::cout << "From Process: ";
                printMessage(message.from_process);
                std::cout << "Data: ";
                printMessage(message.msg_data);
                std::cout << "Data Length: ";
                printMessage(message.msg_len);
                std::cout << "Filename: ";
                printMessage(message.file_name);
                std::cout << "Priority: ";
                printMessage(message.priority);
                return handleClient(message);
            default:  //Parent process
                //handle another client request
                continue;
        }
    }
    return false;
}

bool Server::handleClient(Message message) {
    lpid = (long)message.from_process;
    //save file pointer etc
    Message send;
    std::string file_path = "./files/";
    file_path += message.msg_data;
    printMessage("parsing message");
    if (message.file_name && fileExists(file_path)) {
        printMessage("Valid file.");
    } else {
        // Send message to queue that file does not exist
        printMessage("Sending file does not exist");
        send.msg_type = lpid;
        strcpy(send.msg_data, "FileNotExist\0");
        send.msg_len = 0;
        send.from_process = (long)getpid();
        return (send_message(&send) != -1);
    }
    while (running) {
        //service the client with the file
        Message recv;
        if (read_message(lpid, &recv) == -1) {
            return false;
        }
    }
    return true;
}
