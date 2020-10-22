#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Poprawne uzycie programu \"%s rodzaj_akcji numer_sygnalu\"\n", argv[0]);
        exit(1);
    }

    pid_t pid = fork();
    switch(pid) {
        case -1: {
            perror("fork error");
            exit(1);
        }
        case 0: {
            execl("./obsluga.x", "./obsluga.x", argv[1], argv[2], NULL);
            perror("execl error");
            exit(1);
        }
        default: {
            sleep(1);

            kill(pid, 0);
            if(errno == ESRCH) {
                printf("Proces nie istnieje\n");
                exit(1);
            }

            int signalNumb = atoi(argv[2]);
            kill(pid, signalNumb);

        }
    }
    wait(NULL);
}