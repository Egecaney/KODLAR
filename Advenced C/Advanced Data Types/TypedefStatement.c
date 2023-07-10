#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 *  The typedef keywprd is an advanced feature in C that enables you to create your own name for existing data type 
 *  To define a new type name with typedef
 *      1. Write the statement as if a variable of the desired type were being declared
 *      2. Where the name of the declared variable would normally appear, substitute the new type name
 *      3. In front of everything, place the keyword typedef
 *  
 *  Advantages:
 *      1. Added Readability
 *      2. Maintainability (Sürdürülebilirlik)
 *      3. Portable
 * 
 *  Typedef vs Define
 *      We know that the #define is handled by the preprocessor
 *      The typedef is handled by the C compiler, provides more flexibility when it comes to assigning names to derived data types
 */

typedef char* CharPointer;
typedef int*  IPointer;
#define IntPointer  int*

#define Peach int
typedef int Banana;

#define DATA_SIZE   20
#define LOOP_SIZE   10

int main(void){

    IPointer    APtr , *B2Ptr;              /* Same as int *APtri **B2Ptr */
    IPointer    myArray[DATA_SIZE];         /* Same as int *myArray[10] */

    IntPointer  Chalk, Cheese;              /* Same as int *Chalk, int Cheese (Not pointer)*/
    CharPointer Bently, RollsRoyce;         /* Same as char* Bently, char* RollsRoyce */
    
    printf("Enter the number for APtr: ");
    scanf("%d", &APtr);

    Peach TempValue = APtr;
    for(Banana Index = 0; Index < LOOP_SIZE; Index++){
        myArray[Index] = TempValue + Index;
        myArray[Index + LOOP_SIZE] = APtr + Index;
        printf("%d. Index = %d  --  %d. Index = %d\n", (Index+1), myArray[Index], (Index+LOOP_SIZE+1), myArray[Index + LOOP_SIZE]);
    }

    Bently = 'B';
    RollsRoyce = "R";

    printf("APtr = %d\nBently = %c\nRollsRoyce = %s\n", APtr, Bently, RollsRoyce);

    return(0);
}