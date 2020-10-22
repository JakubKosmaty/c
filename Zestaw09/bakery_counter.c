#define _XOPEN_SOURCE   600

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define BARRIER                      __sync_synchronize() 
#define THREADS_NUMBER              4
#define CHECKING_VALUE              100

volatile int testValue = 0;
volatile int thNumbers[THREADS_NUMBER] = {0};
volatile bool entering[THREADS_NUMBER] = {false};

typedef struct {
    int counter;
    int index;
} thData;

void getErrorCode(int code) {
    if (code != 0) {
        printf("Kod błędu: %d\n", code);
        exit(1);
    }
}

void lockThread(int thIndex) { 
    entering[thIndex] = true;
    BARRIER;
  
    int maxThNumber = 0;
    for (int i = 0; i < THREADS_NUMBER; i++) {
        if (thNumbers[i] > maxThNumber) {
            maxThNumber = thNumbers[i];
        }
    }
    
    printf("---------------------\n");
    printf("thIndex: %d\n", thIndex);
    printf("Debug: %d\n", maxThNumber);
    maxThNumber++;
    printf("Debug: %d\n", maxThNumber);
    printf("---------------------\n");
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
    int thIndex = *((int *) data);
    free(data);

    //for (int i = 0; i < CHECKING_VALUE; i++) {
        lockThread(thIndex);
        BARRIER;
        testValue += 1;
        unlockThread(thIndex);
    //}
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t threadsID[THREADS_NUMBER];

    for (int i = 0; i < THREADS_NUMBER; i++) {
        int *thIndex = malloc(sizeof(*thIndex));
        if (thIndex == NULL) {
            exit(1);
        }

        *thIndex = i;
        getErrorCode(pthread_create(&threadsID[i], NULL, threadFunc, thIndex));
    }

    for (int i = 0; i < THREADS_NUMBER; i++) {
        getErrorCode(pthread_join(threadsID[i], NULL));
    }

    printf("Wartosc licznika: %d\n", testValue);
    printf("Prawidlowa wartosc licznika: %d\n", CHECKING_VALUE * THREADS_NUMBER);
}
