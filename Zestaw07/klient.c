#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "msg.h"

int main(int argc, char* argv[]) {
    int pid = getpid();

    char pidStr[16];
    sprintf(pidStr, "/%d", pid);

    int clientMQ = msgCreate(pidStr);
    msgInfo(clientMQ);
    int serverMQ = msgOpen(MQ_SERVER_NAME);

    char operator;
    int numbers[2];

    printf("Zakonczenie procesu: CTRL + D\n");

    while (1) {
        printf("Podaj wyrazenie:\n");
        int res = scanf("%d %c %d", &numbers[0], &operator, &numbers[1]);
        if (res == EOF) break;
        if (res == 3) {
            MsgQueue message;

            message.numbers[0] = numbers[0];
            message.numbers[1] = numbers[1];
            message.operator = operator;

            strncpy(message.clientPID, pidStr, 16);
            msgSend(serverMQ, &message);
            msgRecv(clientMQ, &message);

            if (message.operator == 'd') {
                printf("Nie mozna dzielic przez 0!\n");
            } else if(message.operator == 'o'){
                printf("Nieprawidlowy operator!\n");
            } else {
                printf("Wynik: %d\n", message.numbers[0]);
            }

        } else {
            printf("Nieprawidlowe format: 'liczba operator liczba'\n");
            int ignoreWarning = scanf("%*[^\n]");
            ignoreWarning++;
        }
    }


    msgClose(MQ_SERVER_NAME);
    msgClose(pidStr);
    msgRm(pidStr);
    printf("Czyszczenie klienta...\n");
}