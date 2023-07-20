#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <setjmp.h>

/*
 *  The header file <setjmp.h> needs to be included in any source file that uses setjmp or longjmp
 * 
 *  setjmp saves a copy of the program counter and thhe current pointer to the top of the stack
 *  int setjmp(jmp_buf j)
 *      use the variable j to remember where you are now
 *      must be called first
 * 
 *  longjmp is then invoked after setjmp (longjmp(jmp_buf j, int i))
 *      says go back to the place that the j is remembering
 *      restores the process in the state that it existed when it called setjmp
 *          return the value of i so the code can tell when you actually got back here via longjmp()
 *      the contents of the j are destroyed when it is used in a longjmp()
 * 
 *  Often referred to as "unwinding the stack", because you unroll activation records from the stack until you get to the saved one 
 *  
 *  !!! setjump(jmp_buf buf)     : uses buf to remember the current position and returns 0.
 *  !!! longjump(jmp_buf buf, i) : Go back to the place buf is pointing to and return i.
 *  !!! longjmp goes where you last setjmp.
 *  
 *  goto statement implements a local jump of program execution, and the longjmp() and setjmp() functions implement a nonlocal, or far, Jump program.
 * */

jmp_buf Buffer;
int LongJumpIndex = 0;
int SetJumpIndex  = 0;
void DetectedRecovery(void);

int main(void){

    while(true){
        SetJumpIndex = setjmp(Buffer);
        if(SetJumpIndex == 0)
            printf("First Position\n");
        else if(SetJumpIndex == 1)
            printf("Second Position\n");
        else if(SetJumpIndex == 2)
            printf("Third Position\n");
        else{
            printf("Default Position\n");
            break;
        }
        DetectedRecovery();
    }
    return 0;
}

void DetectedRecovery(void){
    printf("In DetectedRecovery() Function\n");
    LongJumpIndex++;
    longjmp(Buffer, LongJumpIndex);
    printf("You will never see this, because of longjmp");
}