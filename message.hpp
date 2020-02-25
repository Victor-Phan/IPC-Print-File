#pragma once
#define MAXMESSAGEDATA (4096 - 16)
#define MESGHDRSIZE (sizeof(Message) - MAXMESGDATA)
#include <iostream>

//type 1 for messages to server
//process id for messages to client
typedef struct {
    long msg_type;
    char msg_data[MAXMESSAGEDATA];
    int msg_len;  //bytes in mesg_data
    bool file_name;
    int priority;
    long from_process;
    bool last_message;
} Message;

template <typename T>
void printMessage(T message) {
    std::cout << message << std::endl;
}

// void printMessageStruct(Message message) {
//     std::cout << "Msg Type: ";
//     printMessage(message.msg_type);
//     std::cout << "From Process: ";
//     printMessage(message.from_process);
//     std::cout << "Data: ";
//     printMessage(message.msg_data);
//     std::cout << "Filename: ";
//     printMessage(message.file_name);
//     std::cout << "Priority: ";
//     printMessage(message.priority);
// }