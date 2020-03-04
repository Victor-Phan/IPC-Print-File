#pragma once
#include "service.hpp"
class Server : public Service {
   private:
     static const std::string FILE_LOCATION;
     static void* createDataMessageThread(void* messageArguments);
   protected:
    long client_pid;
   public:
    Server() = default;
    virtual ~Server() = default;
    bool startServer();
    bool close_queue() {
        return (msgctl(msg_id, IPC_RMID, NULL) == 0);
    }
    bool handleClientFileRequest(Message message);
    bool handleClientFileData(std::string filepath, int priority);
    Message createDataMessage(FileHandler* fileHandler,int priority);
};
