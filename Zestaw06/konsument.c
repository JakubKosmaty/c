#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>

#include "helpers.h"
#include "shmem.h"
#include "sem.h"

int main(int argc, char* argv[]) {
    int tempDesc = shmOpen(SHMNAME);
    int memoryLength = shmSize(tempDesc);
    DataStruct* wpd = (DataStruct*) shmMap(tempDesc, memoryLength);

    FILE *file = fopen(FILE_2, "w");
    if (file == NULL) {
        perror("Open file error");
        exit(1);
    }

    char buffor[64];

    semid semFull = semOpen(SEMNAME_FULL);
    semid semEmpty = semOpen(SEMNAME_EMPTY);

    while (1) {
        int randomNumb = random_number(10000, 100000);
        usleep(randomNumb);

        semP(semFull);
        if (wpd->closed == 1) {
            break;
        }

        int bytes = sprintf(buffor, "%d\n", wpd->buffor[wpd->beg]);

        printf("Konsumuje: %d\n", bytes);
        fwrite(buffor, sizeof(char), bytes, file);
        wpd->beg = (wpd->beg + 1) % BUFFORSIZE;
        semV(semEmpty);
    }

    while (wpd->beg != wpd->end) {
        int bytes = sprintf(buffor, "%d\n", wpd->buffor[wpd->beg]);
        fwrite(buffor, sizeof(char), bytes, file);
        wpd->beg = (wpd->beg + 1) % BUFFORSIZE;
    }

    shmClose(wpd, tempDesc, memoryLength);
    semClose(semFull);
    semClose(semEmpty);
    fclose(file);
}