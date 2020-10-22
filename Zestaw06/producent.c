#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>

#include "shmem.h"
#include "sem.h"
#include "helpers.h"

int main(int argc, char* argv[]) {
    int tempDesc = shmOpen(SHMNAME);
    int memoryLength = shmSize(tempDesc);
    DataStruct* wpd = (DataStruct*) shmMap(tempDesc, memoryLength);

    FILE *file = fopen(FILE_1, "r");
    if (file == NULL) {
        perror("Open file error");
        exit(1);
    }

    semid semFull = semOpen(SEMNAME_FULL);
    semid semEmpty = semOpen(SEMNAME_EMPTY);

    char buffor[64];
    while (fgets(buffor, sizeof(buffor), file)){

        int randomNumb = random_number(10000, 100000);
        usleep(randomNumb);

        semP(semEmpty);

        printf("Produkuje: %s\n", buffor);

        int temp = atoi(buffor);
        wpd->buffor[wpd->end] = temp;
        wpd->end = (wpd->end + 1) % BUFFORSIZE;
        semV(semFull);
    }
    
    wpd->closed = 1;
    semV(semFull);

    shmClose(wpd, tempDesc, memoryLength);
    semClose(semFull);
    semClose(semEmpty);
    fclose(file);
}