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
        // pattern_3(num_things);
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
            printf("Process %d (%d) beginning\n", i, getpid());
            sleep(sleep_time());

            printf("Process %d (%d) exiting\n", i, getpid());
            exit(0); // terminate the child process
        }
    }

    // meanwhile, the parent should wait for all the multiple children to finish
    for (int i = 1; i <= num_things; ++i)
    {
        wait(NULL);
    }

    printf("main (%d) exiting\n", getpid());
}

// fork chain of processes from child to child
void pattern_2(int num_things)
{
    for (int i = 1; i <= num_things; ++i)
    {
        pid_t pid = fork();
        if (pid == 0) // only the children can run this block
        {
            printf("Process %d (%d) beginning\n", i, getpid());
            sleep(sleep_time());

            if (i < num_things)
            {
                printf("Process %d creating Process %d\n", i, i + 1);
            }

            if (i == num_things) // the last child terminates the chain, this
                                 // will make other parents in the else block in
                                 // wait(NULL) to exit the loop
            {
                printf("Process %d (%d) exiting\n", i, getpid());
                exit(0); // exit without creating another child
            }
        }
        else // parent creates one child and wait for it to finish before
             // exiting, while the child creates another child
        {
            wait(NULL);
            if (i - 1 == 0)
            {
                printf("main (%d) exiting\n", getpid());
                break; // for the main
            }
            else
            {
                printf("Process %d (%d) exiting\n", i - 1, getpid());
                exit(0); // for the children to exit
            }
        }
    }
}