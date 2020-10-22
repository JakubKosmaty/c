#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    switch(fork()) {
        case -1: {
            perror("fork error");
            exit(1);
        }
        case 0: {
            exit(0);
        }
    }

    sleep(10);
}