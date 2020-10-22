#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <semaphore.h>

#include "sem.h"

#define FILE    "numer.txt"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Poprawne uzycie programu \"%s nazwa_programu liczba_procesow\"\n", argv[0]);
        exit(1);
    }

    const char* semName = "mysem2";

    semid semPoint = semCreate(semName, 1);
    if(semPoint == SEM_FAILED) {
        exit(1);
    }

    int file;
    if(((file = open(FILE, O_WRONLY | O_CREAT, 0666)) == -1)) {
        perror("Open file error");
        exit(1);
    }

    int bytes = write(file, "0", sizeof("0"));
    if(bytes == -1) {
        perror("Write error");
        exit(1);
    }

    if(close(file) < 0) { 
        perror("Close file error");
        exit(1);
    }

    int processCount = 0;
    for(int i = 0; i < atoi(argv[2]); i++) {
        switch(fork()) {
            case -1: {
                perror("fork error");
                exit(1);
            }
            case 0: {
                char* arr[] = {argv[1], NULL};
                execv(argv[1], arr);
                perror("execl error");
                exit(1);
            }
            default: {
                processCount++;
                break;
            }
        }
    }

    for(int i = 0; i < processCount; i++) {
        wait(NULL);
    }

    semRemove(semName);

    if(((file = open(FILE, O_RDONLY, 0666)) == -1)) {
        perror("Open file error");
        exit(1);
    }

    char buffer[12];
    bytes = read(file, buffer, sizeof(buffer));
    if(bytes == -1) {
        perror("Read error");
        exit(1);
    }

    if(close(file) < 0) { 
        perror("Close file error");
        exit(1);
    }

    int finalNumb = atoi(argv[2]) * 5;
    if(finalNumb == atoi(buffer)) {
        printf("Poprawna liczba w pliku: %d\n", finalNumb);
    } else {
        printf("Nieprawidlowa liczba: %d | %d\n", finalNumb, atoi(buffer));
    }
}