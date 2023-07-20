#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*
 *  IF YOU ARE USED TO USİNG GOTO STATEMENTS, TRY TO TRAIN YOURSELF NOT TO  
 *   
 *  1. A goto statement causes program control to jump to a particular line of code in your program
 *          This branch is made immediately and unconditionally upon execution of the goto
 * 
 *  2. To identify where in the program the branch is to be made, a label is needed.
 *          A label is a name that is formed with the same rules as variable names
 *          The label is placed directly before the statement to which the branch is to be made and must appear in the same function as the goto
 * 
 *  3. PROBLEMS WITH GOTO:
 *      - Programmers who are lazy frequently abuse the goto statement to branch to other portions of their code
 *      - The goto statement interrupts the normal sequential flow of a program
 *            As a result, programs are harder to follow and thus harder to maintein
 * 
 *  4. AVOIDING GOTO:
 *      - In principle, you never need to use the goto statement in a C program, however some programmers develop bad habits
 *      - Most gotos are used for helping ifs, simulating if elses, controlling loops, or are just there because you have programmed yourself into a corner.
 *            - Instead of skipping to the end of a loop and starting the next cycle using a goto statement, use continue
 *            - Instead of leaving a lııp using goto statement, user break. 
 * 
 * */

#ifndef errChk
#define errChk(fCall) if (Error = (fCall), Error <= 0) {goto Error;} else
#endif

#define ParityTypeMessageSize       (int)100
#define NoError                     (int)0
#define DataErrorValue              (int)-1
#define ParityErrorValue            (int)-2
#define DataAndParityErrorValue     (int)-3

void GetTheDataAndParityType(uint8_t *Data, char* ParityType);
int ControlTheDataAndParityType(uint8_t Data, uint8_t ParityType);

int main(void){

    int Error = 0;
    uint8_t Data = 0;
    uint8_t ParityType[ParityTypeMessageSize];
    uint8_t CheckSum = 0;
    printf("\n\t\tParity Bit Calculator\n\n");

    GetTheDataAndParityType(&Data, ParityType);
    errChk(ControlTheDataAndParityType(Data, ParityType[0]));

Calculate:
    for(int Index = 0; Index < 8; Index ++){
        if((Data >> Index) & 0x01 == 1)
            CheckSum++;
    }
    if(ParityType[0] == 'E'){
        if(CheckSum%2 == 0) printf("Parity Bit is 0\n");
        else                printf("Parity Bit is 1\n");
    }
    else if(ParityType[0] == 'O'){
        if(CheckSum%2 == 0) printf("Parity Bit is 1\n");
        else                printf("Parity Bit is 0\n");
    }
    goto Finish;
    
LetsTry:
    GetTheDataAndParityType(&Data, ParityType);
    errChk(ControlTheDataAndParityType(Data, ParityType[0]));
    goto Finish;
    
Error:
    if(Error <= 0){
        switch(Error){
            case 0:
                printf("\nStarting Application ....\n"); 
                goto Calculate;
            case -1: 
                printf("\nThe number is not in the desired range!\nPlease, try again!\n\n");
                break;
            case -2: 
                printf("\nThere is no such parity type!\nPlease, try again!\n\n");
                break;
            case -3: 
                printf("\nWrong choices!\nPlease, try again!\n\n");
                break;
        } 
        goto LetsTry;
    }
    
Finish:
    printf("The process is completed.\n\n");
    return(0);
}

void GetTheDataAndParityType(uint8_t *Data, char* ParityType){
    printf("Please, enter the number between 0 and 255: ");
    scanf("%d", Data);
    printf("For Odd Parity Write O, Even Parity For E\nPlease Select the Parity Type: ");
    scanf("%s", ParityType);
}

int ControlTheDataAndParityType(uint8_t Data, uint8_t ParityType){
    uint8_t DataCheck = (Data >= 0 || Data <= 255);
    uint8_t ParityBitCheck = ((char)ParityType == 'O' || (char)ParityType == 'E');
    switch((DataCheck << 0)|(ParityBitCheck << 1)){
        case 0: return DataAndParityErrorValue; break;
        case 1: return DataErrorValue;          break;
        case 2: return ParityErrorValue;        break;
        case 3: return NoError;                 break;
    }
}