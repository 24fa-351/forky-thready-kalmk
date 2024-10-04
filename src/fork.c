#include "fork.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

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
void pattern_1(int num_things /*num of child processes to create*/)
{
    for (int i = 1; i <= num_things; ++i) // create child processes
    {
        pid_t pid = fork();
        if (pid == 0) // only the children can run this block
        {
            process(i, num_things);
            exit(0); // terminate the child process
        }
    }

    // meanwhile, the parent should wait for all the children to finish
    for (int i = 1; i <= num_things; ++i)
    {
        wait(NULL);
    }
}

// fork chain of processes from child to child
void pattern_2(int num_things)
{
    for (int i = 1; i <= num_things; ++i)
    {
        pid_t pid = fork();
        if (pid == 0) // only the children can run this block
        {
            process(i, num_things);

            if (i == num_things) // the last child terminates the chain, this
                                 // will make other parents in the else block in
                                 // wait(NULL) to exit the loop
            {
                exit(0);
            }
        }
        else // parent creates one child and wait for it to finish before
             // exiting, while the child creates another child
        {
            wait(NULL);
            break;
        }
    }
}

void pattern_3(int num_things)
{
}

void process(int id, int total)
{
    printf("Process %d (%d) beginning\n", id, getpid());

    int sleep_time = (rand() % 8) + 1;
    sleep(sleep_time);

    if (id < total)
    {
        printf("Process %d creating Process %d\n", id, id + 1);
    }

    printf("Process %d (%d) exiting\n", id, getpid());
}