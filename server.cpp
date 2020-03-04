/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: 	server.cpp - This file contains that logic that starts the server and handles connecting clients.
--
--
-- PROGRAM: 		Message Queue Application
--
-- FUNCTIONS:
--                  bool startServer()
--                  bool handleClientFileRequest(Message message)
--                  Message createDataMessage(FileHandler* fileHandler, int priority)
--                  void *createDataMessageThread(void *messageArguments)
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
--                  Server class is able to start the server. Once started, it can read messages that are of type
--                  SERVER_MSG_TYPE. Once it reads a valid message, it will create a process in order to send file 
--                  contents to the client.
--------------------------------------------------------------------------------------------------------------------*/
#include "server.hpp"
const std:: string Server::FILE_LOCATION ="./files/";
/*-----------------------------------------------------------------------------------------------------------------
-- Function:	startServer
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 	Victor Phan
--
-- PROGRAMMER: 	Victor Phan
--
-- INTERFACE:	bool startServer()
--
-- RETURNS:     Returns false if the server fails to read a message for the server or if the server is disconnected.
--
-- NOTES:
--              Opens the message queue and reads message type SERVER_MSG_TYPE. Creates process for each 
--              client that request a file that exists.
--
-------------------------------------------------------------------------------------------------------------------*/
bool Server::startServer() {
    running = true;
    if (open_queue() == -1) {
        return false;
    }
    while (running) {
        Message message;
        if (read_message(SERVER_MSG_TYPE, &message) == -1) {
            printMessage("Failed to read initial message");
            return false;
        }

        switch (lpid = fork()) {
            case -1:
                printMessage("Error creating process");
                break;
            case 0:  //Child process
                //handle processing of client
                printMessage("Client Process connected: : ",false);
                printMessage(message.from_process);
                return handleClientFileRequest(message);
            default:  //Parent process
                //handle another client request
                continue;
        }
        close_queue();
    }
    return false;
}

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	handleClientFileRequest
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 	Victor Phan
--
-- PROGRAMMER: 	Victor Phan
--
-- INTERFACE:	bool handleClientFileRequest(Message message)
--                   message - the message that was received from the client
--
-- RETURNS:     Returns false if file does not exist or failure to put message onto queue.
--
-- NOTES:
--
--              Checks to see if file exists. If file exists Server will begin putting 
--              file contents onto message queue.
-------------------------------------------------------------------------------------------------------------------*/
bool Server::handleClientFileRequest(Message message) {
    lpid = (long)getpid();
    client_pid = (long)message.from_process;
    //save file pointer etc
    Message send;
    std::string file_path = FILE_LOCATION;
    file_path += message.msg_data;
    printMessage("parsing message");
    if (message.file_name && FileHandler::fileExists(file_path)) {
        printMessage("Valid file.");
    } else {
        // Send message to queue that file does not exist
        printMessage("Sending file does not exist");
        send.msg_type = client_pid;
        strcpy(send.msg_data, "FileNotExist\0");
        send.msg_len = 0;
        send.from_process = (long)getpid();
        return (send_message(&send) != -1);
    }
    int priority = message.priority;
    return handleClientFileData(file_path, priority);
}

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	handleClientFileData
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 	Victor Phan
--
-- PROGRAMMER: 	Victor Phan
--
-- INTERFACE:	bool handleClientFileData(std::string filepath, int priority)
--                   filepath - path of file to be read (must be valid)
--                   priority - the client's priority
--
-- RETURNS:     Returns false if file contents cannot be put onto the queue
--
-- NOTES:
--              Opens file to read from. Puts contents of file onto the message queue.
-------------------------------------------------------------------------------------------------------------------*/
bool Server::handleClientFileData(std::string filepath, int priority) {
    FileHandler fileHandler{filepath};
    while (running) {
        //service the client with the file
        Message sendFileData = createDataMessage(&fileHandler,priority);

        //No more to send
        if(sendFileData.msg_len <= 0) {
            //send file complete message
            sendFileData.last_message = true;
            send_message(&sendFileData);
            return true;
        }
        if (send_message(&sendFileData) == -1) {
            return false;
        }
    }
    return true;
}

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	createDataMessage
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 	Victor Phan
--
-- PROGRAMMER: 	Victor Phan
--
-- INTERFACE:	Message createDataMessage(FileHandler* fileHandler, int priority)
--                  fileHandler - contains the file to be read from
--                  priority - the client's priority
--
-- RETURNS:     Returns a Message object containing a part of the file contents
--
-- NOTES:
--              Opens file to read from. Returns a Message object to be put on the Message Queue.
-------------------------------------------------------------------------------------------------------------------*/
Message Server::createDataMessage(FileHandler* fileHandler, int priority) {
    //Priority is implemented by allowing a process to put more or less
    //data on to the message queue
    void* threadRet = nullptr;
    pthread_t tid;
    MessageArgument* args = new MessageArgument{};
    args->file = fileHandler;
    args->priority = priority;
    pthread_create(&tid, NULL, &Server::createDataMessageThread, args);
    pthread_join(tid, &threadRet);
    //Must make sure to delete
    std::string* buf = (std::string*) threadRet;
    // fill in struct
    Message message;
    message.msg_type = client_pid;
    message.from_process = lpid;
    message.file_name = false;
    message.last_message = false;
    message.priority = priority;
    memset(message.msg_data,0,MAXMESSAGEDATA);
    strcpy(message.msg_data,buf->c_str());
    message.msg_len = buf->length();
    delete buf;
    delete args;
    return message;
}

/*-----------------------------------------------------------------------------------------------------------------
-- Function:	createDataMessageThread
--
-- DATE:		February 27, 2020
--
-- REVISIONS:
--
-- DESIGNER: 	Victor Phan
--
-- PROGRAMMER: 	Victor Phan
--
-- INTERFACE:	void* createDataMessageThread(void *messageArguments)
--                  messageArguments - MessageArgument struct
 --                                    contains the file to be read from and priority
--
-- RETURNS:     pointer to string that contains file contents
--
-- NOTES:
--              Thread function opens file to read from. Returns a string with the file's contents
-------------------------------------------------------------------------------------------------------------------*/
void *Server::createDataMessageThread(void *messageArguments) {
    MessageArgument args = *(MessageArgument*)messageArguments;
    FileHandler* fileHandler = args.file;
    int priority = args.priority;
    int bytes = MAXMESSAGEDATA / (MAXMESSAGEDATA - priority + 1);
    std::string* data = new std::string(fileHandler->readFile(bytes));
    return (void*)data;
}

