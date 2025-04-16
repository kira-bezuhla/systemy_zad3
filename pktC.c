#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE
#define _XOPEN_SOURCE 500

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
    pid_t leader_pid = fork();

    if (leader_pid < 0)
    {
        perror("fork error");
        exit(2);
    }
    else if (leader_pid == 0)
    {
        // proces staje sie liderem
        setpgid(0, 0);
        printf("leader PID: %d, PGID: %d\n", getpid(), getpgrp());
        signal(signum, SIG_IGN); // i ignoruje signaly od procesu macierzystego
      
        
        // tworzymy proces, ktory zamieni execlp 
        pid_t runCa_pid = fork();

        if (runCa_pid < 0)
        {
            perror("fork error for runCa");
            exit(5);
        }
        else if (runCa_pid == 0)
        {
            // tworzymy procesy potomne
            execlp("./runCa", "./runCa", argv[1], argv[2], NULL);
            perror("execlp failed");
            exit(6);
        }

        // lider czeka zakonczenia runCa i wypisuje ich PID i status zakonczenia
        
            int status;
            pid_t terminated_pid = wait(&status);
            if (WIFSIGNALED(status))
            {
                printf("runCa process %d killed by signal %d (%s)\n",
                       terminated_pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
            }
            else
            {
                printf("runCa process %d exited with code %d\n", terminated_pid, WEXITSTATUS(status));
            }
        
        // exit(EXIT_SUCCESS);
    }
    else
    {
        // proces macierzysty czeka i wysyla sygnal
        sleep(3);
        pid_t group_id = getpgid(leader_pid);
        if (group_id < 0)
        {
            perror("getpgid error");
            exit(5);
        }
        printf("sending signal %d to group %d\n", signum, group_id);
        kill(-group_id, signum);
        // group_id negatywny, bo chcemy, zeby sygnal byl wyslany grupie procesow
        // If pid is negative, but not -1, sig shall be sent to all processes (excluding an unspecified set of system processes)
        // whose process group ID is equal to the absolute value of pid, and for which the process has permission to send a signal.

        // proces macierzysty czeka na zakonczenie lidera wypisuje jego PID i status zakonczenia
        int status;
        pid_t terminated_pid = waitpid(leader_pid, &status, 0);
        if (WIFSIGNALED(status))
        {
            printf("leader process %d killed by signal %d (%s)\n",
                   terminated_pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
        }
        else
        {
            printf("leader process %d exited with code %d\n", terminated_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
