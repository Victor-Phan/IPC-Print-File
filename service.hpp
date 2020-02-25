#pragma once
#define SERVER_MSG_TYPE 1
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "filehandler.hpp"
#include "message.hpp"

class Service {
  protected:
    key_t mkey;
    pid_t pid;
    int msg_id;
  public:
    //Default key generation
    Service() : mkey(ftok(".", 'z')) {
        printMessage(mkey);
    }
    virtual ~Service() = default;
    int open_queue();
    int send_message(Message *qbuf);
    int read_message(long type, Message *qbuf);

};