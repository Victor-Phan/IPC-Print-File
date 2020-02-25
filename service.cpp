#include "service.hpp"

int Service::open_queue() {
    int qid;
    qid = msgget(mkey, IPC_CREAT | 0660);
    if (qid == -1)
    {
        printMessage("Failed to open queue");
        return -1;
    }
    msg_id = qid;
    return qid;
}
int Service::send_message(Message *qbuf) {
    int result;
    result = msgsnd(msg_id, qbuf, qbuf->msg_len, 0);
    if (result == -1)
    {
        printMessage("Failed to send Message");
        return -1;
    }
    return result;
}
int Service::read_message(long type, Message *qbuf) {
    int result, length;
    length = sizeof(Message);
    result = msgrcv(msg_id, qbuf, length, type, 0);
    if (result == -1)
    {
        printMessage("Failed to read Message");
        return -1;
    }
    return result;
}