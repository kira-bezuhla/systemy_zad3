#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[]) //"<numer sygnalu> <ilosc procesow potomnych>"
{
    if (argc != 3)
    {
        printf("incorrect arguments\n");
        exit(1);
    }

    int signum = atoi(argv[1]);
    int child_count = atoi(argv[2]);

    // tworzymy procesy potomne
    for (int i = 0; i < child_count; i++)
    {
        pid_t child_pid = fork();
        if (child_pid < 0)
        {
            perror("fork error");
            exit(3);
        }
        else if (child_pid == 0)
        {
            execlp("./runA", "./runA", argv[1], "default", NULL);
            perror("execlp error");
            exit(4);
        }
    }

    return 0;
}