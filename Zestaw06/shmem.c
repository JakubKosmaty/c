#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "shmem.h"

int shmCreate(const char* name, int size) {
    int tempDesc = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0666);
    if(tempDesc == -1) {
        perror("Create Error");
        exit(1);
    }

    if(ftruncate(tempDesc, size) == -1) {
        perror("Set Length Error");
        exit(1);
    }

    return tempDesc;
}

int shmOpen(const char* name) {
    int tempDesc = shm_open(name, O_RDWR, 0666);
    if(tempDesc == -1) {
        perror("Open Error");
        exit(1);
    }

    return tempDesc;
}

void shmRm(const char* name) {
    int tempDesc = shm_unlink(name);
    if(tempDesc == -1) {
        perror("UnLink Error");
        exit(1);
    }
}

void* shmMap(int fd, int size) {
    void* tempSrc = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(tempSrc == (void*)-1) {
        perror("Map Error");
        exit(1);
    }

    return tempSrc;
}

void shmClose(void *ptr, int fd, int size) {
    if(munmap(ptr, size) == -1) {
        perror("UnMap Error");
        exit(1);
    }

    if(close(fd) == -1) {
        perror("Close Error");
        exit(1);
    }
}   

int shmSize(int fd) {
    struct stat tempStat;
    if(fstat(fd, &tempStat) == -1) {
        perror("fstat Error");
        exit(1);
    }

    return tempStat.st_size;
}

void shmInfo(int fd) {
    struct stat tempStat;
    if(fstat(fd, &tempStat) == -1) {
        perror("fstat Error");
        exit(1);
    }

    printf("ID: %ld\nINO: %lu\nMODE: %d\nLINK: %ld\nUID: %d\nGID: %d\nRDEV: %ld\nSIZE: %ld\nBLKSIZE: %ld\nBLOCKS: %ld\nATIME: %ld\nMTIME: %ld\nCTIME: %ld\n", tempStat.st_dev, tempStat.st_ino, tempStat.st_mode, tempStat.st_nlink, tempStat.st_uid, tempStat.st_gid, tempStat.st_rdev, tempStat.st_size, tempStat.st_blksize, tempStat.st_blocks, tempStat.st_atime, tempStat.st_mtime, tempStat.st_ctime);
}