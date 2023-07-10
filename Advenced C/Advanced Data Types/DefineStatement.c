#include <stdio.h>

/*  
 * 1. In C programming you can use this directive to symbolic, or manifest, constants in a program 
 * 2. Preprocessor directives run until the first newline the #
 *      - a directive is limited to one line in length
 *      - the combination backslash/newline is deleted begins
 *          - you can spread the directive over several physical lines
 *          - these lines still constitute a single logical lines
 * 3. It might be necessary to use constant values that are related to the particular computer on which the program is running
 *      - might have to do with the use of a particular computer memory address, a filename, or the number of bits contained in a computer word
 */

#define YES     1
#define NO      0

#define TWO_PI  2.0*3.141592654

#define MAXIMUM_DATAValues  100

/*
 * #define is a preprocessor directive. 
 * Data defined by the #define macro definition are preprocessed, so that your entire code can use it. 
 * This can free up space and increase compilation times.
 * 
 * const variables are considered variables, and not macro definitions. 
 * 
 * The big advantage of const over #define is type checking. 
 * #defines can’t be type checked, so this can cause problems when trying to determine the data type. 
 * If the variable is, instead, a constant then we can grab the type of the data that is stored in that constant variable. 
 */

#define PI  3.14159f
const float Pi = 3.14159f;

int main(void){

    int Choice = 0;
    int KeepGoing = YES;
    printf("\nIf you wanna start the processor Write(1)!\nIf you don't wanna Write(0).\n");
    printf("Choice: ");
    scanf("%d",&Choice);

    while(KeepGoing == YES){
        KeepGoing = NO;
        if(Choice == YES){

            float Radius = 0.0;
            float FirstData[MAXIMUM_DATAValues];
            float IncrementalDataValue = 0.0;
            float SummationOfDatas = 0.0;

            printf("\nSTEP 1\nEnter the radius of the circle: ");
            scanf("%f", &Radius);
            printf("The Area of the circle: %f\n", (TWO_PI*Radius));

            printf("\nSTEP 2\nEnter the fist data: ");
            scanf("%f", &FirstData[0]);
            printf("Enter the incremental data value: ");
            scanf("%f", &IncrementalDataValue);

            SummationOfDatas = FirstData[0];
            for(int Index = 0; Index < MAXIMUM_DATAValues-1; Index++){
                FirstData[Index+1] = FirstData[Index] + IncrementalDataValue;
                SummationOfDatas += FirstData[Index+1];
            }

            for(int Index = 0; Index < MAXIMUM_DATAValues; Index++)
                printf("%d. Data = %.2f\n", (Index+1), FirstData[Index]);

            printf("\nSummation: %.2f",SummationOfDatas);
        }
        else if(Choice == NO){
            printf("\nThe program is finished!\n");
        }
        else{
            printf("\nWrong Choice!\nDo you wanna keep going? (YES:1, NO:0)\nEnter the Choice: ");
            scanf("%d", &Choice);

            if(Choice == YES){
                KeepGoing = YES;
            }
            else if(Choice == NO){
                KeepGoing = NO;
                printf("\nThe program is finished!\n");
            }
            else{
                KeepGoing = NO;
                printf("\nAgain wrong choice you idiot! I won't ask you again, you don't deserve!");
            }
        }
    }
    return(NO);   
}