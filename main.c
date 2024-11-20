#include <stdio.h>
#include <stdlib.h>

#include "fork.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <num_things> <pattern>\n", argv[0]);
        return -1;
    }
    int num_things = atoi(argv[1]);
    int pattern = atoi(argv[2]);

    if (!(num_things > 1 || num_things < 256))
    {
        printf("Invalid number of processes.\n");
        return -1;
    }

    if (pattern > 3 || pattern < 1)
    {
        printf("Invalid pattern number.\n");
        return -1;
    }

    run(num_things, pattern);

    return 0;
}