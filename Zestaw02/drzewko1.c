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
    } while(res && errno == EINTR);

    return res;
}

int main(int argc, char* argv[]) {
    int count = 0;
    pid_t childpid;

    for(int i = 0; i < 3; i++) {
        childpid = fork();
        if(childpid == -1) {
            perror("fork error");
            exit(1);
        }
        else if(childpid == 0) {
            msleep(i * 100 + 100);
            break;
        }
        else {
            count++;
        }
    }

    int pid = getpid();
    printf("UID: %d | GID: %d | PID: %d | PPID: %d | PGID: %d\n", getuid(), getgid(), pid, getppid(), getpgid(pid));

    for(int i = 0; i < count; i++) {
        wait(NULL);
    }
}