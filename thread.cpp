#include <stdio.h>
#include "thread.h"

// Constructor
MotherEagle::MotherEagle(int f)
             :feed(f)
{

}

// Constructor
BabyEagle::BabyEagle()
{

}

void MotherEagle::ThreadFunc()
{
    Thread::ThreadFunc();
    for (i = 0; i < feed; i++)
    {
        printf("Mom sleeping...\n");
        goto_sleep();
        Delay();

        printf("Food ready, release children...\n");
        food_ready();
        Delay();

    }

}

void BabyEagle::ThreadFunc()
{
    Thread::ThreadFunc();
    while (1) {
        Delay();            // play for a while
        printf("Baby ready to eat...\n");
        ready_to_eat();     // get hungry
        Delay();            // eat for a while
                            // you may call Delay() multiple times
                            //(use a random number generate)
                            // to have a longer and more random delay.
        finish_eating();    // finish eating
        printf("Baby finished eating\n");
                            // do some other thing
    }
}
