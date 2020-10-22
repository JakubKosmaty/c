#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FILE                "schowek.txt"
#define MAX_SIZE_BUFFER     512

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Poprawne uzycie programu \"%s nazwa_potoku\"\n", argv[0]);
        exit(1);
    }

    int safeFile;
    if(((safeFile = open(FILE, O_WRONLY | O_CREAT, 0666)) == -1)) {
        perror("Open file error");
        exit(1);
    }
    
    int fifoDesc;
    if((fifoDesc = open(argv[1], O_RDONLY)) == -1) {
        perror("Open file error");
        exit(1);
    }

    char buffer[MAX_SIZE_BUFFER];
    int bytes;
    while((bytes = read(fifoDesc, buffer, sizeof(buffer))) > 0) {
        int writeBytes =  write(safeFile, buffer, bytes);
        printf("Liczba odczytanych bajtow z potoku: %d\n", bytes);
        printf("Liczba zapisanych bajtow do pliku: %d\n", writeBytes);
    }

    if(close(safeFile) < 0) {
        perror("Close file error"); 
        exit(1);
    }

    if(close(fifoDesc) < 0) {
        perror("Close file error"); 
        exit(1);
    }
}