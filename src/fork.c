#include "fork.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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

void pattern_1(int num_things)
{
    
}

void pattern_2(int num_things)
{
    
}

void pattern_3(int num_things)
{
    
}