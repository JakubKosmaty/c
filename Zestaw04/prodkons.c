#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FILE_1              "magazyn.txt"
#define FILE_2              "schowek.txt"
#define MAX_SIZE_BUFFER     512

// https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
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

void saveData(int fileDesc[2]) {
    if(close(fileDesc[0]) < 0) {
        perror("Close file error"); 
        exit(1);
    }

    int storageFile;
    if(((storageFile = open(FILE_1, O_RDONLY)) == -1)) {
        perror("Open file error");
        exit(1);
    }

    char buffer[MAX_SIZE_BUFFER];
    int readBytes;
    while((readBytes = read(storageFile, buffer, sizeof(buffer))) > 0) {
        int writeBytes = write(fileDesc[1], buffer, readBytes);
        printf("Liczba zapisanych bajtow do potoku: %d\n", writeBytes);
        printf("Liczba odczytanycg bajtow z pliku: %d\n", readBytes);
    }

    if(close(fileDesc[1]) < 0) {
        perror("Close file error"); 
        exit(1);
    }

    int randomNumb = random_number(10000, 100000);
    usleep(randomNumb);
}

void loadData(int fileDesc[2]) {
    if(close(fileDesc[1]) < 0) {
        perror("Close file error"); 
        exit(1);
    }

    int safeFile;
    if(((safeFile = open(FILE_2, O_WRONLY | O_CREAT, 0666)) == -1)) {
        perror("Open file error");
        exit(1);
    }

    char buffer[MAX_SIZE_BUFFER];
    int readBytes;
    while((readBytes = read(fileDesc[0], buffer, sizeof(buffer))) > 0) {
        int writeBytes = write(safeFile, buffer, readBytes);
        printf("Liczba odczytanych bajtow z potoku: %d\n", readBytes);
        printf("Liczba zapisanych bajtow do pliku: %d\n", writeBytes);
    }

    if(close(fileDesc[0]) < 0) {
        perror("Close file error"); 
        exit(1);
    }
}


int main(int argc, char* argv[]) {
    int fileDesc[2];
    if(pipe(fileDesc) < 0) {
        perror("pipe error");
        exit(1); 
    }

    pid_t pid = fork();
    switch(pid) {
        case -1: {
            perror("fork error");
            exit(1);
        }
        case 0: {
            loadData(fileDesc);
            break;
        }
        default: {
            saveData(fileDesc);
            wait(NULL);
            break;
        }
    }
}