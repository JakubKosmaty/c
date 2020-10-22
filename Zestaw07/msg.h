#ifndef MSG_H
#define MSG_H

#include <mqueue.h>

typedef struct {
    char clientPID[16];
    int numbers[2];
    char operator;
} MsgQueue;

#define MQ_SERVER_NAME          "/serverMQ"
#define MAX_MESSAGE             10;

int msgCreate(const char *name);

int msgOpen(const char *name);

void msgClose(const char *name);

void msgRm(const char* name);

void msgSend(int msgid, MsgQueue *msg);

void msgRecv(int msgid, MsgQueue *msg);

void msgInfo(int msgid);


#endif