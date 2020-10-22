 #define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>

#include "sem.h"
#include "shmem.h"
#include "helpers.h"

int main(int argc, char* argv[]) {
    shmCreate(SHMNAME, sizeof(DataStruct));
    semCreate(SEMNAME_EMPTY, BUFFORSIZE);
    semCreate(SEMNAME_FULL, 0);

    int tempDesc = shmOpen(SHMNAME);
    int memoryLength = shmSize(tempDesc);
    DataStruct* wpd = (DataStruct*) shmMap(tempDesc, memoryLength);

    wpd->beg = 0;
    wpd->end = 0;
    wpd->closed = 0;

    shmClose(wpd, tempDesc, memoryLength);

    pid_t pid = fork();
    switch (pid) {
        case -1: {
            perror("fork error");
            exit(1);
        }
        case 0: {
            execl("./konsument.x", "./konsument.x", NULL);
            perror("execl error");
            exit(1);
            break;
        }
        default: {
            if (fork() == 0) { // Aby program powrocił
                execl("./producent.x", "./producent.x", NULL);
                perror("execl error");
                exit(1);
            }
            break;
        }
    }

    wait(NULL);
    wait(NULL);

    shmRm(SHMNAME);
    semRemove(SEMNAME_EMPTY);
    semRemove(SEMNAME_FULL);
}