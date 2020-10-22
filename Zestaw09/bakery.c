#define _XOPEN_SOURCE   600

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define THREADS_NUMBER              4
#define BARRIER                      __sync_synchronize() 
#define CONSOLE_CLEAR               printf("\033c")
#define CONSOLE_DEF                 printf("\033[0m\033[m")
#define CONSOLE_POS(x, y)           printf("\033[%d;%dH", x, y)
#define CONSOLE_BOLD_TEXT(s)        printf("\033[1m%s\033[m", s)
#define CONSOLE_COLOR_TEXT(c, s)    printf("\033[%dm%s\033[m", c, s)

volatile int testValue = 0;
volatile int thNumbers[THREADS_NUMBER] = {0};
volatile bool entering[THREADS_NUMBER] = {false};

typedef struct {
    int counter;
    int index;
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

void getErrorCode(int code) {
    if (code != 0) {
        printf("Kod błędu: %d\n", code);
        exit(1);
    }
}

int randomNumber(int min_num, int max_num) {
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
    fflush(stdout);
}

void lockThread(int thIndex) { 
    entering[thIndex] = true;
    BARRIER;
  
    int maxThNumber = thNumbers[0];
    for (int i = 0; i < THREADS_NUMBER; i++) {
        if (thNumbers[i] > maxThNumber) {
            maxThNumber = thNumbers[i];
        }
    }

    maxThNumber++;
    thNumbers[thIndex] = maxThNumber;
    BARRIER;
    entering[thIndex] = false;
    BARRIER;

    for (int i = 0; i < THREADS_NUMBER; i++) { 
        while (entering[i]) { 
        }
        BARRIER;
        while (thNumbers[i] != 0 && (thNumbers[i] < thNumbers[thIndex]  || (thNumbers[i] == thNumbers[thIndex] && i < thIndex))) {
        }
    } 
}

void unlockThread(int thIndex) {
    BARRIER;
    thNumbers[thIndex] = 0; 
} 

void* threadFunc(void* data) {
    thData *threadData = (thData *)data;
 
    lockThread(threadData->index);

    threadData->counter = testValue + 1;

    CONSOLE_POS(3 + threadData->index, 32);
    CONSOLE_COLOR_TEXT(RED, "W trakcie");
    fflush(stdout);

    BARRIER;

    int randNumb = randomNumber(150000, 1500000);
    usleep(randNumb);

    testValue = threadData->counter;

    CONSOLE_POS(3 + threadData->index, 12);
    CONSOLE_COLOR_TEXT(GREEN, "Zakonczono");

    CONSOLE_POS(3 + threadData->index, 32);
    printf("         ");
    fflush(stdout);

    unlockThread(threadData->index);

    return NULL;
}

int main(int argc, char* argv[]) {
    printInfo();

    pthread_t threadsID[THREADS_NUMBER];
    thData threadsData[THREADS_NUMBER];

    for (int i = 0; i < THREADS_NUMBER; i++) {
        CONSOLE_POS(3 + i, 1);
        printf("Watek");
        CONSOLE_POS(3 + i, 8);
        printf("%d", i);
        fflush(stdout);

        threadsData[i].index = i;
        threadsData[i].counter = 0;

        getErrorCode(pthread_create(&threadsID[i], NULL, threadFunc, &threadsData[i]));
    }

    for (int i = 0; i < THREADS_NUMBER; i++) {
        getErrorCode(pthread_join(threadsID[i], NULL));
   
        CONSOLE_POS(20 + i, 1);
        printf("Zakonczono watek: NR: %d | ID: %p", i, &threadsID[i]);
        fflush(stdout);
    }

    printf("\n");
    printf("Wartosc licznika: %d\n", testValue);
    printf("Prawidlowa wartosc licznika: %d\n", THREADS_NUMBER);
}
