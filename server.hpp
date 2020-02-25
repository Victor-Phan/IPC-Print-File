#pragma once
#include <unistd.h>
#include "service.hpp"

class Server : public Service {
   protected:
    bool running = false;
   public:
    Server() : Service(), running(true) {}
    bool startServer();
    bool close_queue() {
        return (msgctl(msg_id, IPC_RMID, NULL) == 0);
    }
    bool handleClient(Message message);
};