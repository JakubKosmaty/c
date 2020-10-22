#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>    

// https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds
int msleep(long msec) {
    struct timespec ts;
    int res;

    if(msec < 0) {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

int main(int argc, char* argv[]) {
    for(int i = 0; i < 3; i++) {
        switch(fork()) {
            case -1: {
                perror("fork error");
                exit(1);
            }
            case 0: {

                int pid = getpid();
                setpgid(pid, pid);
                msleep(i * 100 + 100);
            }
        }
    }
    
    int pid = getpid();
    printf("UID: %d | GID: %d | PID: %d | PPID: %d | PGID: %d\n", getuid(), getgid(), pid, getppid(), getpgid(pid));

    while(wait(NULL) > 0);
}