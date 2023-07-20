#include "main.h"
#include "AutomaticVariables.c"
#include "StaticVariables.c"
#include "RegisterVariables.c"
// Not include ExternVariables_Function

/*
 * Storage Classes are used to describe the features of a variable/function
 *		           include the scope, visibility and life-time
 *                 help us to trace the existance of a particular variable during the runtime of a program 
 *
 *  The four storage-class specifiers can be split into two storage durations
 *     1. Automatic storage duration
 *     2. Static storage duration
 */	

int  Counter;
char* Name[2];
extern void WriteCounter(int AmountOfIncrease);
extern void WriteName(int Rank);

int main(){

    printf("\n****** AUTOMATIC VARIABLES ******\n");
    AutoFunction();	

    printf("\n****** EXTERNAL VARIABLES ******\n");
    Counter = 5;
    WriteCounter(10);
    WriteName(1);
    WriteName(2);

    printf("\n****** STATIC VARIABLES ******\n");
    for(int Index=0; Index<2; Index++){
        StaticFunction();
        AgainStaticFunction();
    }
    
    printf("\n****** REGISTER VARIABLES ******\n");
    RegisterFunction();

    return(0);
}

/* To run program 
 * PS D:\Advanced C\Storage_Classes> gcc main.c ExternVariables.c
 * PS D:\Advanced C\Storage_Classes> ./a.exe
 * 
 * OR
 * 
 * PS D:\Advanced C\Storage_Classes> ./Console.exe
 */