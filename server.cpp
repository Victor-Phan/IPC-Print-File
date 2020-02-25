#include "server.hpp"

bool Server::startServer() {
    if (open_queue() == -1) {
        return false;
    }
    while (running) {
        Message message;
        if (read_message(SERVER_MSG_TYPE, &message) == -1) {
            return false;
        }
        switch (pid = fork()) {
            case -1:
                printMessage("Error creating process");
                break;
            case 0:  //Child process
                //handle processing of client
                //pass by value so that there is no seg fault
                return handleClient(message);
            default:  //Parent process
                //handle another client request
                continue;
        }
    }
    return false;
}

bool Server::handleClient(Message message) {
    pid_t client = message.from_process;
    while (running) {
        if (message.file_name && fileExists(message.msg_data)) {
        } else {
            // Send message to queue that file does not exist
            Message send;
            send.msg_type = client;
            strcpy(send.msg_data,"FileNotExist\0");
            send.msg_len = -1;
            send.from_process = getpid();
            return (send_message(&send) != -1);
        }
    }
    return true;
}
