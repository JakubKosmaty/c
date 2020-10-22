#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("pierwszy komunikat");

    execl("./potomny.x", "./potomny.x", NULL);

    printf("drugi komunikat");
}