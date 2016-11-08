// -----------------------------------------------------------
// NAME : Zachary Hill                   User ID: zahill
// DUE DATE : 11/11/2016
// PROGRAM ASSIGNMENT #4
// FILE NAME : thread.h
// PROGRAM PURPOSE :
//    Contains all the class definitions
// -----------------------------------------------------------
#include "ThreadClass.h"

extern Semaphore * Queue;
extern Semaphore * WakeMom;
extern Semaphore * Eating;
extern Semaphore * GetPot;
extern int feedPots;
extern int babyEag;
extern int feedings;
extern int potCount;

class MyThread : public Thread
{
    public:
        MyThread(int n);

    private:
        void ThreadFunc();
};

class MotherEagle : public Thread
{
    public:
        MotherEagle(int f);
        void goto_sleep(void);
        void food_ready(void);

    private:
        int i;
        int k;
        int j;
        int feed;
        void ThreadFunc();
};

class BabyEagle : public Thread
{
    public:
        BabyEagle();
        void ready_to_eat(void);
        void finish_eating(void);

    private:
        void ThreadFunc();
};

