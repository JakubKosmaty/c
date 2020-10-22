#define _XOPEN_SOURCE   600

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

volatile int testValue = 0;

typedef struct {
    int counter;
    int id;
    pthread_mutex_t* mutexID;
} thData;

enum textColors {
    BLACK = 30,
    RED,
    GREEN,
    BROWN,
    BLUE,
    MAGENTA,
    CYAN,
    LIGHTGRAY,
};

#define THREADS_NUMBER              4
#define CONSOLE_CLEAR               printf("\033c")
#define CONSOLE_DEF                 printf("\033[0m\033[m")
#define CONSOLE_POS(x, y)           printf("\033[%d;%dH", x, y)
#define CONSOLE_BOLD_TEXT(s)        printf("\033[1m%s\033[m", s)
#define CONSOLE_COLOR_TEXT(c, s)    printf("\033[%dm%s\033[m", c, s)

int randomNumber(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1;
    } else {
        low_num = max_num + 1;
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}


void printInfo() {
    CONSOLE_CLEAR;
    CONSOLE_POS(1, 1);
    CONSOLE_BOLD_TEXT("Watek");
    CONSOLE_POS(1, 8);
    CONSOLE_BOLD_TEXT("Nr");
    CONSOLE_POS(1, 12);
    CONSOLE_BOLD_TEXT("Sekcja prywatna");
    CONSOLE_POS(1, 32);
    CONSOLE_BOLD_TEXT("Sekcja krytyczna");
}

void* threadFunc(void* data) {
    thData *threadData = (thData *)data;

    pthread_mutex_lock(threadData->mutexID);

    threadData->counter = testValue + 1;

    CONSOLE_POS(3 + threadData->id, 32);
    CONSOLE_COLOR_TEXT(RED, "W trakcie");
    fflush(stdout);
    int randNumb = randomNumber(150000, 1500000);
    usleep(randNumb);

    testValue = threadData->counter;

    pthread_mutex_unlock(threadData->mutexID);

    CONSOLE_POS(3 + threadData->id, 12);
    CONSOLE_COLOR_TEXT(GREEN, "Zakonczono");

    CONSOLE_POS(3 + threadData->id, 32);
    printf("         ");
    fflush(stdout);
    
    return NULL;
}

void getErrorCode(int code) {
    if(code != 0) {
        printf("Kod błędu: %d\n", code);
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    printInfo();

    pthread_mutex_t myMutex;
    getErrorCode(pthread_mutex_init(&myMutex, NULL));

    CONSOLE_POS(19, 1);
    printf("Utworzono mutex: %p\n", &myMutex);

    pthread_t threadsID[THREADS_NUMBER];
    thData threadsData[THREADS_NUMBER];

    for(int i = 0; i < THREADS_NUMBER; i++) {
        threadsData[i].id = i;
        threadsData[i].counter = 0;
        threadsData[i].mutexID = &myMutex;

        CONSOLE_POS(3 + i, 1);
        printf("Watek");
        CONSOLE_POS(3 + i, 8);
        printf("%d", i);

        getErrorCode(pthread_create(&threadsID[i], NULL, threadFunc, &threadsData[i]));
    }

    for(int i = 0; i < THREADS_NUMBER; i++) {
        getErrorCode(pthread_join(threadsID[i], NULL));
   
        CONSOLE_POS(20 + i, 1);
        printf("Zakonczono watek: NR: %d | ID: %p", i, &threadsID[i]);
    }

    printf("\n");
    getErrorCode(pthread_mutex_destroy(&myMutex));
    printf("Usunieto mutex\n");

    printf("Wartosc licznika: %d\n", testValue);
    printf("Prawidlowa wartosc licznika: %d\n", THREADS_NUMBER);
}
