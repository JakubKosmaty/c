#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "procinfo.h"

void signalHandler(int sigNumb) {
    printf("Numer sygnału: %d\n", sigNumb);
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Poprawne uzycie programu \"%s rodzaj_akcji numer_sygnalu\"\n", argv[0]);
        exit(1);
    }

    int signalNumb = atoi(argv[2]);

    if(signalNumb == SIGKILL || signalNumb == SIGSTOP) {
        printf("Nie mozna obsluzyc sygnalow SIGKILL i SIGSTOP\n");
        exit(1);
    }

    procinfo(argv[0]);

    switch(*argv[1])
    {
        case 'd': {
            signal(signalNumb, SIG_DFL);
            break;
        }
        case 'i': {
            signal(signalNumb, SIG_IGN);
            break;
        }
        case 'p': {
            signal(signalNumb, signalHandler);
            break;
        }
        default: {
            printf("Niepoprawny rodzaj akcji!\nDozwolone: d,i,p\n");
            exit(1);
            break;
        }
    }

    pause();
    //raise(signalNumb);
}