#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <semaphore.h>

#include "sem.h"

#define FILE    "numer.txt"

int main(int argc, char* argv[]) {
    const char *semName = "mysem2";

    semid semPoint = semOpen(semName);
    if(semPoint == SEM_FAILED) {
        exit(1);
    }

    printf("PID: %d\n", getpid());
    semInfo(semPoint);

    int file;

    for(int i = 0; i < 5; i++) {
        
        semV(semPoint);

        if(((file = open(FILE, O_RDONLY, 0666)) == -1)) {
            perror("Open file error");
            exit(1);
        }

        char buffer[12];
        int bytes = read(file, buffer, sizeof(buffer));
        if(bytes == -1) {
            perror("Read error");
            exit(1);
        }

        if(close(file) < 0) { 
            perror("Close file error");
        }

        usleep(500);

        if(((file = open(FILE, O_WRONLY, 0666)) == -1)) {
            perror("Open file error");
            exit(1);
        }

        int temp = atoi(buffer) + 1;

        char str[12];
        int numbSize = sprintf(str, "%d", temp);
        bytes = write(file, str, numbSize);
        if(bytes == -1) {
            perror("Write error");
            exit(1);
        }

        if(close(file) < 0) { 
            perror("Close file error");
        }

        printf("PID: %d\n", getpid());
        semInfo(semPoint);

        semP(semPoint);
    }

    printf("PID: %d\n", getpid());
    semInfo(semPoint);

    semClose(semPoint);
}