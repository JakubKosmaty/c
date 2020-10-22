#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>

#include "sem.h"

semid semCreate(const char* name, int val) {
    if(val < 0) {
        printf("Nieprawidlowa wartosc semafora!\n");
        return SEM_FAILED;
    }

    semid semTemp = sem_open(name, O_CREAT, 0644, val);
    if(semTemp == SEM_FAILED) {
        perror("Create Sem Error");
        return SEM_FAILED;
    }

    printf("Semafor utworzony\n");
    return semTemp;
}

void semRemove(const char* name) {
    if(sem_unlink(name) == -1) {
        perror("Remove Sem Error");
        exit(1);
    }

    printf("Semafor usuniety\n");
}

semid semOpen(const char* name) {
    semid semTemp = sem_open(name, 0);
    if(semTemp == SEM_FAILED) {
        perror("Open Sem Error");
        return SEM_FAILED;
    }

    printf("Semafor otworzony\n");
    return semTemp;
}

void semClose(semid sem) {
    if(sem_close(sem) == -1) {
        perror("Close Sem Error");
        exit(1);
    }

    printf("Semafor zamkniety\n");
}

void semV(semid sem) {
    if(sem_post(sem) == -1) {
        perror("Post Sem Error");
        exit(1);
    }

    printf("Semafor opuszczony\n");
}

void semP(semid sem) {
    if(sem_wait(sem) == -1) {
        perror("Wait Sem Error");
        exit(1);
    }

    printf("Semafor uniesiony\n");
}

void semInfo(semid sem) {
    int semVal;
    if(sem_getvalue(sem, &semVal) == -1) {
        perror("Info Sem Error");
        exit(1);
    }

    printf("Wartosc semafora: %d\n", semVal);
}
