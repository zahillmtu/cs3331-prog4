#include <stdio.h>
#include "thread.h"

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
            printf("Exiting %d\n", num);
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

void BabyEagle::finish_eating(void)
{
    // Tell mom I'm done
    Eating->Signal();
}
