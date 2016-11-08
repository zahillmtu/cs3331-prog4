// -----------------------------------------------------------
// NAME : Zachary Hill                   User ID: zahill
// DUE DATE : 11/11/2016
// PROGRAM ASSIGNMENT #4
// FILE NAME : thread.h
// PROGRAM PURPOSE :
//    Contains all the class definitions
// -----------------------------------------------------------
#include "ThreadClass.h"

class MyThread : public Thread
{
    public:
        MyThread(int n);

    private:
        void ThreadFunc();
};
