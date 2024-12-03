#include "fork.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

unsigned int sleep_time()
{
    return (rand() % 8) + 1;
}

void run(int num_of_processes, int pattern)
{
    switch (pattern)
    {
    case 1:
        printf("Pattern 1:\n");
        pattern_1(num_of_processes);
        break;
    case 2:
        printf("Pattern 2:\n");
        pattern_2(num_of_processes);
        break;
    }
}

// fork multiple processes from the main
void pattern_1(int num_of_processes)
{
    for (int ix = 1; ix <= num_of_processes; ++ix)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            fprintf(stderr, "Process %d (%d) beginning\n", ix, getpid());
            sleep(sleep_time());

            fprintf(stderr, "Process %d (%d) exiting\n", ix, getpid());
            exit(0);
        }
    }

    for (int ix = 1; ix <= num_of_processes; ++ix)
    {
        wait(NULL);
    }

    fprintf(stderr, "main (%d) exiting\n", getpid());
}

void pattern_2_child_process(int process_num, int num_of_processes)
{
    fprintf(stderr, "Child process %d (%d) beginning\n", process_num, getpid());

    int time = sleep_time();

    if (process_num < num_of_processes)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            pattern_2_child_process(process_num + 1, num_of_processes);
        }
        else if (pid > 0)
        {
            sleep(time);
            fprintf(stderr, "Child process %d (%d) exiting\n", process_num,
                    getpid());
            exit(0);
        }
        else
        {
            fprintf(stderr, "Error forking child process %d\n", process_num);
        }
    }
}

// fork chain of processes from child to child
void pattern_2(int num_of_processes)
{
    int start_process_num = 0;
    pid_t pid = fork();

    if (pid == 0)
    {
        pattern_2_child_process(start_process_num + 1, num_of_processes);
    }
    else if (pid > 0)
    {
        fprintf(stderr, "Parent process (%d) beginning\n", getpid());
        sleep(sleep_time());
        fprintf(stderr, "Parent process (%d) exiting\n", getpid());
        exit(0);
    }
    else
    {
        fprintf(stderr, "Error forking parent process\n");
    }
}