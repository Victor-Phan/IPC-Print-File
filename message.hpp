#pragma once
#define MAXMESSAGEDATA (4096 - 16)
#define MESGHDRSIZE (sizeof(Message) - MAXMESGDATA)
#include <iostream>

//type 1 for messages to server
//type 2 for messages to client
typedef struct {
    long msg_type;
    char msg_data[MAXMESSAGEDATA];
    int msg_len;  //bytes in mesg_data
    bool file_name;
    pid_t from_process;
} Message;

template <typename T>
void printMessage(T message) {
    std::cout << message << std::endl;
}