/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: 	service.cpp - This file contains logic pertaining to message queue operations.
--
--
-- PROGRAM: 		Message Queue Application
--
-- FUNCTIONS:
--                  int open_queue()
--                  int send_message(Message* qbuf)
--                  int read_message(long type, Message *qbuf)
--
-- DATE: 			February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 		Victor Phan
--
-- PROGRAMMER: 		Victor Phan
--
-- NOTES:
--                  Service class contains methods that can open, write to, and read from a message queue.
--
--------------------------------------------------------------------------------------------------------------------*/
#include "service.hpp"

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	open_queue
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- INTERFACE:	int open_queue()
--
-- RETURNS:     Returns queue if if successful. -1 if unsuccessful.
--
-- NOTES:
--              Opens the message queue with the specified key.
--
-------------------------------------------------------------------------------------------------------------------*/
int Service::open_queue() {
    int qid;
    qid = msgget(mkey, IPC_CREAT | 0660);
    if (qid == -1) {
        printMessage("Failed to open queue");
        return -1;
    }
    msg_id = qid;
    return qid;
}

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	send_message
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- INTERFACE:	int send_message(Message *qbuf)
--
-- RETURNS:     Returns number of bytes put onto the message queue. -1 on failure
--
-- NOTES:
--              Opens the message queue with the specified key.
--
-------------------------------------------------------------------------------------------------------------------*/
int Service::send_message(Message *qbuf) {
    int result, length;
    length = sizeof(struct Message);
    result = msgsnd(msg_id, qbuf, length, 0);
    if (result == -1) {
        printMessage("Failed to send Message");
        return -1;
    }
    return result;
}

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	read_message
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- INTERFACE:	int read_message(long type, Message *qbuf)
--                  type - message type to be read
--                  qbuf - will contain the data that was read from the bugger
--
-- RETURNS:     Returns number of bytes read from the message queue. -1 on failure
--
-- NOTES:
--              WIll populate the Message structure on success.
--
-------------------------------------------------------------------------------------------------------------------*/
int Service::read_message(long type, Message *qbuf) {
    int result, length;
    length = sizeof(struct Message);
    result = msgrcv(msg_id, qbuf, length, type, 0);
    if (result == -1) {
        printMessage("Failed to read Message");
        return -1;
    }
    return result;
}
