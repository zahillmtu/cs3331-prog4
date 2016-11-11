// -----------------------------------------------------------
// NAME : Zachary Hill                   User ID: zahill
// DUE DATE : 11/11/2016
// PROGRAM ASSIGNMENT #4
// FILE NAME : thread.cpp
// PROGRAM PURPOSE :
//     Holds functionality of baby and mother eagle classes.
//     Methods are implemented here
// -----------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "thread.h"

char momDone;

// -----------------------------------------------------------
// FUNCTION MotherEagle::MotherEagle :
//    Constructor for the Mother eagle class
// PARAMETER USAGE :
//    f - number of feedings
// FUNCTION CALLED :
//    N/A
// -----------------------------------------------------------
MotherEagle::MotherEagle(int f)
             :feed(f)
{

}

// -----------------------------------------------------------
// FUNCTION BabyEagle::BabyEagle :
//    Constructor for the Baby eagle class
// PARAMETER USAGE :
//    n - baby eagle number
// FUNCTION CALLED :
//    N/A
// -----------------------------------------------------------
BabyEagle::BabyEagle(int n)
           :num(n)
{

}

// -----------------------------------------------------------
// FUNCTION printWrap :
//    A wrapper method for printing using write()
// PARAMETER USAGE :
//    buf - A character array of size 100 containing
//          the print statement
// FUNCTION CALLED :
//    write()
// -----------------------------------------------------------
void MotherEagle::printWrap(char buf[100]) {
    write(1, buf, strlen(buf));
}

// -----------------------------------------------------------
// FUNCTION MotherEagle::ThreadFunc :
//    Function called by Begin(), controls the general flow
//    of the Mother eagle, sleeping and feeding the babies
// PARAMETER USAGE :
//    N/A
// FUNCTION CALLED :
//    Delay()
//    goto_sleep()
//    food_ready()
// -----------------------------------------------------------
void MotherEagle::ThreadFunc()
{
    Thread::ThreadFunc();

    sprintf(buf, "Mother eagle started.\n");
    printWrap(buf);

    for (i = 0; i < feed; i++)
    {
        goto_sleep();
        Delay();

        sprintf(buf, "Mother eagle says \"Feeding (%d)\"\n", i + 1);
        printWrap(buf);
        food_ready();
        Delay();

    }

    sprintf(buf, "Mother eagle retires after serving %d feedings."
                 " Game is over!!!\n", feed);
    printWrap(buf);
    momDone = 1;
}

// -----------------------------------------------------------
// FUNCTION printWrap :
//    A wrapper method for printing using write()
// PARAMETER USAGE :
//    buf - A character array of size 100 containing
//          the print statement
// FUNCTION CALLED :
//    write()
// -----------------------------------------------------------
void BabyEagle::printWrap(char buf[100]) {
    write(1, buf, strlen(buf));
}

// -----------------------------------------------------------
// FUNCTION BabyEagle::ThreadFunc :
//    Function called by Begin(), controls the general flow
//    of the baby eagle, eating and coming back
// PARAMETER USAGE :
//    N/A
// FUNCTION CALLED :
//    Delay()
//    ready_to_eat()
//    finish_eating()
// -----------------------------------------------------------
void BabyEagle::ThreadFunc()
{
    Thread::ThreadFunc();
    char space = ' ';
    sprintf(buf, "%*c Baby eagle %d started.\n", num - 1, space, num);
    printWrap(buf);

    while (1) {
        Delay();            // play for a while
        sprintf(buf, "%*c Baby eagle %d ready to eat.\n", num - 1, space, num);
        printWrap(buf);
        ready_to_eat();     // get hungry
        Delay();            // eat for a while
                            // you may call Delay() multiple times
                            //(use a random number generate)
                            // to have a longer and more random delay.
        finish_eating();    // finish eating
        sprintf(buf,"%*c Baby eagle %d finishes eating.\n", num - 1, space, num);
        printWrap(buf);
                            // do some other thing
    }
}
