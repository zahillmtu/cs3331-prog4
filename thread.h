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
extern char momDone;
extern int feedPots;
extern int babyEag;
extern int feedings;
extern int potCount;

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
        char buf[100];
        void ThreadFunc();
        void printWrap(char*);
};

class BabyEagle : public Thread
{
    public:
        BabyEagle(int n);
        void ready_to_eat(void);
        void finish_eating(void);

    private:
        void ThreadFunc();
        void printWrap(char*);
        int num;
        int m;
        char buf[100];
};

