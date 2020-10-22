#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Poprawne uzycie programu \"%s plik_macierzysty plik_docelowy\"", argv[0]);
        exit(1);
    }

    int mainFile;
    if(((mainFile = open(argv[1], O_RDONLY)) == -1)) {
        perror("Open file error");
        exit(1);
    }

    int targetFile;
    if(((targetFile = open(argv[2], O_WRONLY | O_CREAT, 0666)) == -1)) { // http://permissions-calculator.org/ Mode ustawiony na RW dla wszystkich
        perror("Open file error");
        exit(1);
    }

    char buffer[1024];
    int bytes;
    while((bytes = read(mainFile, buffer, sizeof(buffer))) > 0) {
        write(targetFile, buffer, bytes);
    }

    if(close(mainFile) < 0 || close(targetFile) < 0) { 
        perror("Close file error"); 
        exit(1); 
    }

    return 0;    
}   