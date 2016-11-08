#include "thread.h"

void MotherEagle::goto_sleep(void)
{
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
    // wait to be allowed a pot
    Queue->Wait();

    // check in 1 by 1
    GetPot->Wait();
    potCount = potCount - 1;
    // if you are the last one, wake up mom
    if (potCount == 0)
    {
        WakeMom->Signal();
    }
    GetPot->Signal(); // allow next eagle to get a pot
}

void BabyEagle::finish_eating(void)
{
    // Tell mom I'm done
    Eating->Signal();
}
