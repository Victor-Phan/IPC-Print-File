#pragma once
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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
    int open_queue(key_t keyval);
    int send_message(Message *qbuf);
    int read_message(long type, Message *qbuf);

};