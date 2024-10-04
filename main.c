#include <stdio.h>
#include <stdlib.h>

#include "fork.h"

int main(int argc, char *argv[])
{
    int num_things = atoi(argv[1]);
    if (!(num_things > 1 || num_things < 256))
    {
        fprintf(stderr, "Invalid number of processes.\n");

        return 1;
    }

    int pattern = atoi(argv[2]);
    if (pattern > 3 || pattern < 1)
    {
        fprintf(stderr, "Invalid pattern number.\n");

        return 1;
    }

    run(num_things, pattern);

    return 0;
}