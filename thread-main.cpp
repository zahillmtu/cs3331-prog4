// -----------------------------------------------------------
// NAME : Zachary Hill                   User ID: zahill
// DUE DATE : 11/11/2016
// PROGRAM ASSIGNMENT #4
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
//     Program is used to run and solve the Hungry Eagle
//     "game". A game in which a mother eagle fills feeding
//     pots and baby eagles eat from those pots.
// -----------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "thread.h"

int potCount;
int feedPots;
int babyEag;
int feedings;
Semaphore * Queue;
Semaphore * WakeMom;
Semaphore * Eating;
Semaphore * GetPot;


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

// -----------------------------------------------------------
// FUNCTION main :
//    Creates child threads to slove the Hungry eagles
//    problem. Initializes semaphores for thread control.
//    Starts the "game".
// PARAMETER USAGE :
//    argv[1] - The number of feeding pots
//    argv[2] - The number of Baby Eagles
//    argv[3] - The number of feedings
// FUNCTION CALLED :
//    MotherEagle()
//    BabyEagle()
// -----------------------------------------------------------
int main(int argc, char* argv[])
{
    char buf[100];
    int m = 0;
    // Default values will be 10
    feedPots = 10;
    babyEag = 10;
    feedings = 10;

    if (atoi(argv[1]) != 0)
    {
        feedPots = atoi(argv[1]);
    }
    if (atoi(argv[2]) != 0)
    {
        babyEag = atoi(argv[2]);
    }
    if (atoi(argv[3]) != 0)
    {
        feedings = atoi(argv[3]);
    }

    // Set up Semaphores
    potCount = 0;
    momDone = 0;
    Queue = new Semaphore("", 0);
    WakeMom = new Semaphore("", 1);
    Eating = new Semaphore("", feedPots);
    GetPot = new Semaphore("", 1);

    sprintf(buf, "MAIN: There are %d baby eagles, %d feeding pots"
                 ", and %d feedings.\n", babyEag, feedPots, feedings);
    printWrap(buf);
    sprintf(buf, "MAIN: Game starts!!!!!\n");
    printWrap(buf);

    // Start mom Thread
    MotherEagle momEagle(feedings);
    momEagle.Begin();

    // Start baby threads
    BabyEagle *babyEagles[babyEag];
    for (m = 1; m <= babyEag; m++)
    {
        babyEagles[m] = new BabyEagle(m);
        babyEagles[m]->Begin();
    }

    // wait for all child threads
    momEagle.Join();
    for (m = 1; m <= babyEag; m++)
    {
        babyEagles[m]->Join();
    }

    return 0;
}
