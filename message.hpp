#pragma once
#define MAXMESSAGEDATA (4096 - 16)
#define MESGHDRSIZE (sizeof(Message) - MAXMESGDATA)
#include <iostream>

//type 1 for messages to server
//type 2 for messages to client
typedef struct {
    long msg_type;
    long msg_id;
    int msg_len;  //bytes in mesg_data
    char msg_data[MAXMESSAGEDATA];
} Message;

template <typename T>
void printMessage(T message) {
    std::cout << message << std::endl;
}