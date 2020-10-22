#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FILE                "magazyn.txt"
#define MAX_SIZE_BUFFER     512

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Poprawne uzycie programu \"%s nazwa_potoku\"\n", argv[0]);
        exit(1);
    }

    int storageFile;
    if((storageFile = open(FILE, O_RDONLY)) == -1) {
        perror("Open file error");
        exit(1);
    }

    int fifoDesc;
    if((fifoDesc = open(argv[1], O_WRONLY)) == -1) {
        perror("Open file error");
        exit(1);
    }

    char buffer[MAX_SIZE_BUFFER];
    int bytes;
    while((bytes = read(storageFile, buffer, sizeof(buffer))) > 0) {
        int writeBytes = write(fifoDesc, buffer, bytes);
        printf("Liczba zapisanych bajtow do potoku: %d\n", writeBytes);
        printf("Liczba odczytanch bajtow z pliku: %d\n", bytes);
    }

    if(close(fifoDesc) < 0) {
        perror("Close file error"); 
        exit(1);
    }
}
