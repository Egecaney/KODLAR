#include "main.h"

/*   External Variables:
 *
 *   1. The extern storage class simply tells us that a variable is defined elsewhere
 *      NOT within the same block where it is used
 *
 *   2. An extern variable is a global variable initialized with a legal value where it is declared in order to be used elsewhere
 *      An extension to the concept of the global variable
 *   
 *   3. The main purpose of the using extern variables is that they can be accessed between two different files which are part of a large program
 *      Functions contained in separate files can communicate through extern variables
 * 
 *   4. The extern storage class is used to give a reference of a global variable that is visible to ALL the program files
 */

extern int  Counter;
extern char* Name[];

void WriteCounter(int AmountOfIncrease){
    printf("Old Counter Value: %d\n",Counter);
    Counter = Counter + AmountOfIncrease;
    printf("New Counter Value: %d\n",Counter);

    Name[0] = "Aselsan - TAI";
    Name[1] = "Roketsan - Havelsan";
}

void WriteName(int Rank){
    printf("%s\n", Name[Rank-1]);
}