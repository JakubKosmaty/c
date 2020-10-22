#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


int main(int argc, char* argv[]) {
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);

    for(int i = 0; i < 2; i++) {
        pid_t pid = fork();
        switch(pid) {
            case -1: {
                perror("fork error");
                exit(1);
            }
            case 0: {
                if(i == 0) {
                    execl("./producent.x", "./producent.x", myfifo, NULL);
                    perror("execl error");
                    exit(1);
                }
                else {
                    execl("./konsument.x", "./konsument.x", myfifo, NULL);
                    perror("execl error");
                    exit(1);
                }
                break;
            }
        }
    }

    for(int i = 0; i < 2; i++) {
        wait(NULL);
    }
    unlink(myfifo);
}
