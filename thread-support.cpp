// -----------------------------------------------------------
// NAME : Zachary Hill                   User ID: zahill
// DUE DATE : 11/11/2016
// PROGRAM ASSIGNMENT #4
// FILE NAME : thread-support.cpp
// PROGRAM PURPOSE :
//     Holds support functionality of baby and mother eagle
//     classes. Methods are implemented here
// -----------------------------------------------------------

#include <stdio.h>
#include "thread.h"

// -----------------------------------------------------------
// FUNCTION MotherEagle::goto_sleep :
//    Tells the mother eagle thread to wait to be woken by
//    a baby eagle thread
// PARAMETER USAGE :
//    N/A
// FUNCTION CALLED :
//    Wait()
// -----------------------------------------------------------
void MotherEagle::goto_sleep(void)
{
    sprintf(buf, "Mother eagle takes a nap.\n");
    printWrap(buf);
    WakeMom->Wait(); // wait to be woken up

    // wait for all babies to finish eating
    for (j = 1; j <= feedPots; j++)
    {
        Eating->Wait();
    }
}

// -----------------------------------------------------------
// FUNCTION MotherEagle::food_ready :
//    Used to tell baby eagles that the food is ready
// PARAMETER USAGE :
//    N/A
// FUNCTION CALLED :
//    Signal()
// -----------------------------------------------------------
void MotherEagle::food_ready(void)
{
    // Reset number of available pots
    potCount = feedPots;
    // Let more baby eagles eat
    for (k = 1; k <= feedPots; k++)
    {
        Queue->Signal();
    }
}

// -----------------------------------------------------------
// FUNCTION BabyEagle::ready_to_eat :
//    Baby eagle is ready to eat, method finds a pot to use
//    and wakes the mother eagle if not pots available
// PARAMETER USAGE :
//    N/A
// FUNCTION CALLED :
//    Wait()
//    Signal()
// -----------------------------------------------------------
void BabyEagle::ready_to_eat(void)
{
    char space = ' ';
    // wait to be allowed a pot
    Queue->Wait();

    // check in 1 by 1
    GetPot->Wait();
    if (momDone)
    {
        if (potCount > 0)
        {
            sprintf(buf, "%*c Baby eagle %d is eating using feeding pot %d.\n",
                 num - 1, space, num, potCount);
            printWrap(buf);
            potCount = potCount - 1;
            sprintf(buf, "%*c Baby eagle %d finishes eating.\n",
                 num - 1, space, num);
            printWrap(buf);
            GetPot->Signal();
            Queue->Signal();
            Exit();
        }
        else {
            GetPot->Signal();
            Queue->Signal();
            Exit();
        }
    }
    sprintf(buf, "%*c Baby eagle %d is eating using feeding pot %d.\n",
                 num - 1, space, num, potCount);
    printWrap(buf);
    potCount = potCount - 1;
    if (momDone)
    {
        sprintf(buf, "%*c Baby eagle %d finishes eating.\n",
                 num - 1, space, num);
        printWrap(buf);
        GetPot->Signal();
        Exit();
    }
    // if you are the last one, wake up mom
    if (potCount == 0)
    {
        sprintf(buf, "%*c Baby eagle %d sees all feeding pots are empty"
                     " and wakes up the mother.\n", num - 1, space, num);
        printWrap(buf);
        sprintf(buf, "Mother eagle is awoke by baby eagle %d and starts"
                     " preparing food.\n", num);
        printWrap(buf);
        WakeMom->Signal();
    }
    GetPot->Signal(); // allow next eagle to get a pot
}

// -----------------------------------------------------------
// FUNCTION BabyEagle::finish_eating :
//    baby eagle tells the mother it has finished eating
// PARAMETER USAGE :
//    N/A
// FUNCTION CALLED :
//    Signal()
// -----------------------------------------------------------
void BabyEagle::finish_eating(void)
{
    // Tell mom I'm done
    Eating->Signal();
}
