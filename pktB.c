#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>



int main(int argc, char *argv[]) //"<numer sygnalu dla procesu potomnego> <numer sygnalu dla procesu macierzystego> <mode: default | ignore | custom>"
{
    if (argc != 4)
    {
        printf("incorrect arguments\n");
        exit(1);
    }

    pid_t child_id = fork();
    if (child_id < 0)
    {
        perror("fork error");
        exit(2);
    }
    else if (child_id == 0)
    {
        execlp("./runA", "./runA", argv[1], argv[3], (char *)NULL);
        perror("execlp failed");
        exit(3);
    }
    else
    {
        sleep(3);
        if (kill(child_id, 0) != 0)
        {
            perror("process does not exist");
            exit(4);
        }        
        kill(child_id, atoi(argv[2]));
        int status;
        printf("child ID: %d\n", wait(&status));
        if (WIFSIGNALED(status)) { //if process was killed by signal
            printf("child was killed by signal: %d (%s)\n", 
                   WTERMSIG(status), strsignal(WTERMSIG(status)));
        }else{
            printf("child exited normally with code: %d\n", WEXITSTATUS(status));
        }

        
    }

    return 0;
}