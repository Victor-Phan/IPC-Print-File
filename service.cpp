#include "service.hpp"

int Service::open_queue(key_t keyval) {
    int qid;
    qid = msgget(keyval, IPC_CREAT | 0660);
    if (qid == -1)
    {
        return -1;
    }
    msg_id = qid;
    return qid;
}
int Service::send_message(Message *qbuf) {
    int result, length;
    length = sizeof(Message);
    result = msgsnd(msg_id, qbuf, length, 0);
    if (result == -1)
    {
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
        return -1;
    }
    return result;
}