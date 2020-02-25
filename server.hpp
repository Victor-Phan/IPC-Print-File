#pragma once
#include "service.hpp"
class Server : public Service {
   protected:
   public:
    Server() = default;
    virtual ~Server() = default;
    bool startServer();
    bool close_queue() {
        return (msgctl(msg_id, IPC_RMID, NULL) == 0);
    }
    bool handleClient(Message message);
};