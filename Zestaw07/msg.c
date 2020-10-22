#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#include "msg.h"

int msgCreate(const char* name) {
    if (name[0] != '/') {
        printf("Nazwa musi zaczynac sie od '/'");
        exit(1);
    }

    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MESSAGE;
    attr.mq_msgsize = sizeof(MsgQueue);
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    mqd_t tempDesc = mq_open(name, O_RDONLY | O_CREAT | O_EXCL, 0666, &attr);
    if (tempDesc == (mqd_t)-1) {
        perror("msgCreate Error");
        exit(1);
    }

    return tempDesc;
}

int msgOpen(const char *name) {
    mqd_t tempDesc = mq_open(name, O_WRONLY);
    if (tempDesc == (mqd_t)-1) {
        perror("msgOpen Error");
        exit(1);
    }

    return tempDesc;
}

void msgClose(const char *name) {
    int tempDesc = msgOpen(name);
    if (mq_close(tempDesc) == -1) {
        perror("msgClose Error");
        exit(1);
    }
}

void msgRm(const char *name) {
    if (mq_unlink(name) == -1) {
        perror("msgRm Error");
        exit(1);
    }
}

void msgSend(int msgid, MsgQueue *msg) {
    if (mq_send(msgid, (const char *)msg, sizeof(MsgQueue), 0) == -1) {
        perror("msgSend Error");
        exit(1);
    }

}

void msgRecv(int msgid, MsgQueue *msg) {
    if (mq_receive(msgid, (char *) msg, sizeof(MsgQueue), NULL) == -1) {
        if(errno != EINTR) {
            perror("msgRecv Error");
            exit(1);
        }
    }
}

void msgInfo(int msgid) {
    struct mq_attr attr;
    if (mq_getattr(msgid, &attr) == -1) {
        perror("msgInfo Error");
        exit(1);
    }

    printf("------\nAtrybuty kolejki:\nmq_flags: %ld\nmq_maxmsg: %ld\nmq_msgsize: %ld\nmq_curmsgs: %ld\n------\n", attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
}