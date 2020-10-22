#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/stat.h>

#include "shmem.h"

int main(int argc, char* argv[]) {
    if((argc != 2 && argc != 3) || strlen(argv[1]) > 1) {
        printf("Poprawne uzycie programu \"%s argument argument_opcjonalny\"\n", argv[0]);
        exit(1);
    }

    const char* shmName = "myShm0";

    if (argv[1][0] == 'c') {
        int size = atoi(argv[2]);
        shmCreate(shmName, size);
    } else if(argv[1][0] == 'd') {
        shmRm(shmName);
    } else if(argv[1][0] == 'r') {
        int tempDesc = shmOpen(shmName);
        int memoryLength = shmSize(tempDesc);
        char *wpd = (char*) shmMap(tempDesc, memoryLength);

        printf("%s\n", wpd);

        shmClose(wpd, tempDesc, memoryLength);

    } else if(argv[1][0] == 'w') {
        int tempDesc = shmOpen(shmName);
        int memoryLength = shmSize(tempDesc);
        char* wpd = (char*) shmMap(tempDesc, memoryLength);

        int c;
        size_t index = 0;
        while((c = fgetc(stdin)) != EOF) {
            wpd[index++] = (char) c;
            if (index >= memoryLength) {
                perror("Segmentation Fault");
                exit(1);
            }
        }

        printf("Read %zu\n", index);
        shmClose(wpd, tempDesc, memoryLength);
    } else if(argv[1][0] == 'i') {
        int tempDesc = shmOpen(shmName);
        shmInfo(tempDesc);
    } else {
        printf("Nieprawidlowy argument\n");
        exit(1);
    }
}