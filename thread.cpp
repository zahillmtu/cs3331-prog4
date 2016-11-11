#include <iostream>
#include <stdio.h>
#include <string.h>
#include "thread.h"

char momDone;

// Constructor
MotherEagle::MotherEagle(int f)
             :feed(f)
{

}

// Constructor
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
