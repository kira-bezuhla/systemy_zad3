#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

void handler(int signum)
{
    printf("got signal %d: %s\n", signum, strsignal(signum));
}
// dla uruchomienia argumenty <numer sygnalu> <mode: default | ignore | custom>
int main(int argc, char *argv[])
{
    printf("process ID: %d\n", getpid());
    if (argc != 3)
    {
        printf("incorrect arguments\n");
        exit(1);
    }

    int signum = atoi(argv[1]);
    char *mode = argv[2];

    if (strcmp(mode, "default") == 0)
    {
        signal(signum, SIG_DFL);
        printf("default handling of signal %d\n", signum);
    }
    else if (strcmp(mode, "ignore") == 0)
    {
        signal(signum, SIG_IGN);
        printf("ignoring signal %d\n", signum);
    }
    else if (strcmp(mode, "custom") == 0)
    {
        signal(signum, handler);
        printf("custom handling of signal %d\n", signum);
    }
    else
    {
        printf("mode unknown %s\n", mode);
        return 1;
    }

    pause();

    return 0;
}