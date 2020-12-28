// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < which; num++) {
    	for(int i=0;i<200000000;i++);
    	printf("Doing the %s thread in %d level!!\n", currentThread->getName(),num);
    	if(num%4==0)
    		interrupt->OneTick();
    	scheduler->Print();
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("First");
    Thread *t1 = new Thread("Second");
    Thread *t2 = new Thread("Third");
    Thread *t3 = new Thread("Forth");

    t->Fork(SimpleThread, 15);
    t1->Fork(SimpleThread,7);
    t2->Fork(SimpleThread,15);
    t3->Fork(SimpleThread,20);

    /*
    typedef enum {milad,Mehdi,Kazim} name;
    name person;
    person = Kazim;
    if(person == milad )
    	printf("name : %s \n", "milad" );
    else if(person == Mehdi)
    	printf("name : %s \n", "Mehdi" );
    else if(person == Kazim)
    	printf("name : %s \n", "Kazim" );
*/
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
    	ThreadTest1();
    	break;
    default:
    	printf("No test specified.\n");
    	break;
    }
}

