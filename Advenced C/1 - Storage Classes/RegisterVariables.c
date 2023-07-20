#include "main.h"

/*  REGISTER STORAGE
 *  A processor register (CPU register) is one of a small set of data holding places that are part of the computer processor
 *      - A register may hold an instructon, a storage address, or any kind of data
 * 
 *  The register storage class is used to define local variables than should be stored in a register instead of RAM(memory)
 *      Makes the use variables to be much faster than that of the variables stored in the memory during the runtime.
 *     
 *  The register storage class should only be used for variables that require quick access
 *      The variables which are most frequently used in a C program
 *      If a function uses a particular variable heavily
 * 
 *  The lifetime of register variables remains only when control is within the block.
 *  The variable stored in a register has a maximum size equal to the register size.
 * 
 *  (!) You cannot have unary(&) operator applied to it (as it does not have a memory location)
 *  (!) Only LOCAL, not be GLOBAL
 */

void RegisterFunction(){

    /* ! Wrong  
     * register int x = 15;
     * int *a = &x;
     */

    int x = 15;
    register int *a = &x;
    printf("Register X: %d -- Assignment A: %d\n\n", x, a);
    
}

