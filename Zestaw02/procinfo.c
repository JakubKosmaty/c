#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>

#include "procinfo.h"

int procinfo(const char *name) {
    int pid = getpid();
    printf("Name: %s | UID: %d | GID: %d | PID: %d | PPID: %d | PGID: %d\n", name, getuid(), getgid(), pid, getppid(), getpgid(pid));
    return 0;
}