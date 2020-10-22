#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

#include "sem.h"

int main(int argc, char* argv[]) {
    if(argc != 2 || strlen(argv[1]) > 1) {
        printf("Poprawne uzycie programu \"%s argument\"\n", argv[0]);
        exit(1);
    }

    const char* semName = "mysem";

    if(argv[1][0] == 'i') {
        semid tempSem = semCreate(semName, 2);
        if(tempSem == SEM_FAILED) {
            exit(1);
        }

        semInfo(tempSem);
        semClose(tempSem);
    } else if(argv[1][0] == 'r') {
        semRemove(semName);
    } else if(argv[1][0] == 'p') {
        semid tempSem = semOpen(semName);
        if(tempSem == SEM_FAILED) {
            exit(1);
        }

        semP(tempSem);
        semInfo(tempSem);
        semClose(tempSem);
    } else if(argv[1][0] == 'v') {
        semid tempSem = semOpen(semName);
        if(tempSem == SEM_FAILED) {
            exit(1);
        }

        semV(tempSem);
        semInfo(tempSem);
        semClose(tempSem);
    } else if(argv[1][0] == 'q') {
        semid tempSem = semOpen(semName);
        if(tempSem == SEM_FAILED) {
            exit(1);
        }

        semInfo(tempSem);
        semClose(tempSem);
    } else {
        printf("Nieprawidlowy argument\n");
        exit(1);
    }
}