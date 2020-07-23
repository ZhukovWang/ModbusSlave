#include <stdio.h>
#include <string.h>

#include "test/all_test.h"

int main(int argc, char *argv[])
{
    if (strcmp(argv[1],"test") == 0)
    {
        test_all();
    }
    return 0;
}

