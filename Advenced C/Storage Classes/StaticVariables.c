#include "main.h"

/* 
 * Static Storage
 *      The Static storage class can be used on local and global variables, as well as functions
 *      When applied to local variables it instructs the compiler to keep the variable in existance during the life-time of the program
 *      When applied to global variables, the static modifier causes that variable's scope to be restricted to the file in which it is declared
 *      When applied to functions, the static function can be called only from within the same as the function appears  
 *
 *      Static Variables should not be decleared inside a structure
 *      It is possible to declare a structure
 *          - Inside a function (stack segment)
 *          - Allocate memory dynamically(heap segment)
 *          - It can be even global
 */

void StaticFunction(){

    static int StaticCounter = 100;
    // StaticCounter = 100;                     // If I initialize the value in here, static storage will be useless. All StaticCounter will be "(int)100".     
    int LocalVariable = 100;

    printf("Static Variable: %d -- Local Variable: %d\n",StaticCounter, LocalVariable);

    StaticCounter++;
    LocalVariable++;
    
}

void AgainStaticFunction(){
    StaticFunction();
}






