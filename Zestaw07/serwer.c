#define _XOPEN_SOURCE   600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "msg.h"

volatile sig_atomic_t serverStop;

int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

int result(int number1, int number2, char* operator) {
    if (*operator == '+') {
        return number1 + number2;
    } else if (*operator == '-') {
        return number1 - number2;
    } else if (*operator == '*') {
        return number1 * number2;
    } else if (*operator == '/') {
        if (number2 == 0) {
            *operator = 'd';
            return 0;
        }
        return number1 / number2;
    } else {
        *operator = 'o';
        return 0;
    }
}

void signalHandler(int sigNumb) {
    serverStop = 1;
}

int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);

    int serverMQ = msgCreate(MQ_SERVER_NAME);
    msgInfo(serverMQ);
    
    MsgQueue message;

    printf("Zakonczenie procesu: CTRL + C\n");

    while (!serverStop) {
        msgRecv(serverMQ, &message);
        if(errno == EINTR) { 
            errno = 0;
            break;
        }

        printf("Serwer odebral wiadomosc\nTrwa liczenie...\n");
        int randomNumb = random_number(55000, 550000);
        usleep(randomNumb);

        message.numbers[0] = result(message.numbers[0], message.numbers[1], &message.operator); 

        int clientMQ = msgOpen(message.clientPID);

        msgSend(clientMQ, &message);
        printf("Serwer wyslal wynik\n");
        msgClose(message.clientPID);
    }

    signal(SIGINT, SIG_DFL);
    msgClose(MQ_SERVER_NAME);
    msgRm(MQ_SERVER_NAME);

    printf("Czyszczenie serwera...\n");
}