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

    int signalNumb = atoi(argv[2]);

    pid_t pid = fork();
    switch(pid) {
        case -1: {
            perror("fork error");
            exit(1);
        }
        case 0: {
            int pid = getpid();
            setpgid(pid, pid);

            signal(signalNumb, SIG_IGN);

            for(int i = 0; i < 3; i++) {
                switch(fork()) {
                    case -1: {
                        perror("fork error");
                        exit(1);
                    }
                    case 0: {            
                        execl("./obsluga.x", "./obsluga.x", argv[1], argv[2], NULL);
                        perror("execl error");
                        exit(1);
                    }
                }
            }

            for(int i = 0; i < 3; i++) {
                printf("Status zakonczenia: %d\n", wait(NULL));
            }

            break;
        }
        default: {
            sleep(1);

            kill(-pid, 0);
            if(errno == ESRCH) {
                printf("Proces nie istnieje\n");
                exit(1);
            }

            kill(-pid, signalNumb);

            printf("Status zakonczenia: %d\n", wait(NULL));
        }
    }
    
}