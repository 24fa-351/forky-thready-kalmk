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

void run(int num_things, int pattern)
{
    switch (pattern)
    {
    case 1:
        printf("Pattern 1:\n");
        pattern_1(num_things);
        break;
    case 2:
        printf("Pattern 2:\n");
        pattern_2(num_things);
        break;
    case 3:
        printf("Pattern 3:\n");
        pattern_3(num_things);
        break;
    }
}

// fork multiple processes from the main
void pattern_1(int num_things)
{
    for (int ix = 1; ix <= num_things; ++ix)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            printf("Process %d (%d) beginning\n", ix, getpid());
            sleep(sleep_time());

            printf("Process %d (%d) exiting\n", ix, getpid());
            exit(0);
        }
    }

    for (int ix = 1; ix <= num_things; ++ix)
    {
        wait(NULL);
    }

    printf("main (%d) exiting\n", getpid());
}

// fork chain of processes from child to child
void pattern_2(int num_things)
{
    for (int ix = 1; ix <= num_things; ++ix)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            printf("Process %d (%d) beginning\n", ix, getpid());
            sleep(sleep_time());

            if (ix < num_things)
            {
                printf("Process %d creating Process %d\n", ix, ix + 1);
            }

            if (ix == num_things)
            {
                printf("Process %d (%d) exiting\n", ix, getpid());
                exit(0);
            }
        }
        else
        {
            wait(NULL);
            if (ix - 1 == 0)
            {
                printf("main (%d) exiting\n", getpid());
                break;
            }
            else
            {
                printf("Process %d (%d) exiting\n", ix - 1, getpid());
                exit(0);
            }
        }
    }
}

// i tried <_<
void pattern_3(int current_depth)
{
    // pid_t pid_1 = fork();
    // if (pid_1 == 0)
    // {
    //     sleep(sleep_time);
    //     pid_t pid_2 = fork();
    //     if (pid_2 == 0)
    //     {
    //         sleep(sleep_time);
    //     }
    // }
}