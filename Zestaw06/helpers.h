#ifndef HELPERS_H
#define HELPERS_H

#include <sys/wait.h>

#define FILE_1              "magazyn.txt"
#define FILE_2              "schowek.txt"
#define MEMORYLENGTH        10000
#define BUFFORSIZE          16
#define SHMNAME             "myShm1"
#define SEMNAME_EMPTY       "mySem0"
#define SEMNAME_FULL        "mySem1"

typedef struct { 
    int beg;
    int end;
    int buffor[BUFFORSIZE];
    unsigned char closed;
} DataStruct;

int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

#endif
