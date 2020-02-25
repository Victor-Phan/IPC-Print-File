#include "client.hpp"

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
            return false;
        }
        if (recv.msg_len == 0) {
            printMessage("File does not exist on server.");
        } else {
            //create thread to print to screen..?
        }
    }
    return false;
}