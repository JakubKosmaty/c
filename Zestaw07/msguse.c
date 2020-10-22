#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msg.h"

#define MAX_BUFFOR_SIZE     16

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Poprawne uzycie programu \"%s argument nazwa_kolejki\"\n", argv[0]);
        exit(1);
    }

    if(argv[1][0] == 'c') {
        msgCreate(argv[2]);
        msgClose(argv[2]);
    } else if(argv[1][0] == 'd') {
        msgRm(argv[2]);
    } else if(argv[1][0] == 'i') {
        int tempMq = msgOpen(argv[2]);
        msgInfo(tempMq);
    } else if(argv[1][0] == 'w') {
        printf("Zakoncz proces: CTRL + D\n");

        int tempMq = msgOpen(argv[2]);
        char line[MAX_BUFFOR_SIZE];
        int count = 0;

        struct mq_attr attr;
        if (mq_getattr(tempMq, &attr) == -1) {
            perror("msgInfo Error");
            exit(1);
        }

        MsgQueue message;

        while (fgets(line, sizeof(line), stdin)) {
            strncpy(message.clientPID, line, MAX_BUFFOR_SIZE);
            msgSend(tempMq, &message);
            printf("Wyslano do kolejki: %s\n", line);
            count++;

            if(count > attr.mq_maxmsg) {
                printf("Osiagnieto limit wiadomosci w kolejce!\n");
                break;
            }
        }

        msgClose(argv[2]);

    } else if(argv[1][0] == 'r') {
        int tempMq = mq_open(argv[2], O_RDONLY);
        if (tempMq == (mqd_t)-1) {
            perror("msgOpen Error");
            exit(1);
        }

        struct mq_attr attr;
        if (mq_getattr(tempMq, &attr) == -1) {
            perror("msgInfo Error");
            exit(1);
        }

        MsgQueue message;

        printf("Liczba komunikatow w kolejce: %ld\n", attr.mq_curmsgs);

        for(int i = 0; i < attr.mq_curmsgs; i++) {
            msgRecv(tempMq, &message);
            printf("Odczytany komunikat: %s\n", message.clientPID);
        }

        msgClose(argv[2]);

    } else {
        printf("Nieprawidlowy argument\n");
        exit(1);
    }
}