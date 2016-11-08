// -----------------------------------------------------------
// NAME : Zachary Hill                   User ID: zahill
// DUE DATE : 11/11/2016
// PROGRAM ASSIGNMENT #4
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
//
// -----------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "thread.h"

using namespace std;

// -----------------------------------------------------------
// FUNCTION printWrap :
//    A wrapper method for printing using write()
// PARAMETER USAGE :
//    buf - A character array of size 100 containing
//          the print statement
// FUNCTION CALLED :
//    write()
// -----------------------------------------------------------
void printWrap(char buf[100]) {
    write(1, buf, strlen(buf));
}

int main(int argc, char* argv[])
{
    char buf[100];
    int feedPots = 10;
    int babyEag = 10;
    int feedings = 10;

    if (argv[1] != "0")
    {
        feedPots = atoi(argv[1]);
    }
    if (argv[2] != "0")
    {
        babyEag = atoi(argv[2]);
    }
    if (argv[3] != "0")
    {
        feedings = atoi(argv[3]);
    }

    sprintf(buf, "MAIN: There are %d baby eagles, %d feeding pots"
                 ", and %d feedings.\n", babyEag, feedPots, feedings);
    printWrap(buf);

    return 0;
}
