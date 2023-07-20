#include <stdio.h>
#include <stdlib.h>

/**
  * The programs we have discussed are generally structured as functions that call one another in a hierarchical manner.
  * For some types of problems, it is useful to have functions call themselves
  * A recursive function is a function that calls itself either directly or indirectly
  *
  * Recursive functions can be effectively used to succinctly and efficiently solve problems
  *     Commonly used in applications in which the solution to a problem can be expressed in terms of successively applying the same solution to subsets of the problem
  *
  * Iteration with counter-controlled repetition and recursion each gradually approach termination
  *     Iteration keeps modifying counter until the counter assumes a value that makes the loop-continuation condition fail
  *     Recursion keeps producing simpler versions of the original problem until the base case is reached
  *
  **/


int  Factorial(int Number);
void UpAndDown(int Number);
int  SumOfRange(int Number);
char *ReverseFunction(char *String);
int  FindGCD(int FirstNumber, int SecondNumber);

int main(){

    puts("\tFACTORIAL");
    for(int Index = 0; Index < 8; Index++)
        printf("%d! = %d\n", Index, Factorial(Index));

    puts("\n\tUP AND DOWN");
    UpAndDown(1);

    puts("\n\tSUM OF RANGE");
    int Number = 0;
    int Summation = 0;
    printf("Input the last number of the range starting from 1 : ");
    scanf("%d", &Number);
    Summation = SumOfRange(Number);
    printf("The sum of numbers from 1 to %d : %d\n\n", Number, Summation);

    puts("\n\tREVERSE");
    char String[100];
    char *Reverse = NULL;
    printf("Enter the string: ");
    scanf("%s", String);
    printf("The original string is: %s\n", String);
    Reverse = ReverseFunction(String);
    printf("The reversed string is: %s\n", Reverse);

    puts("\n\tFIND GCD");
    int FirstNumber = 0, SecondNumber = 0, GCD = 0;
    printf("Input 1st number: ");
    scanf("%d", &FirstNumber);
    printf("Input 2nd number: ");
    scanf("%d", &SecondNumber);
    GCD = FindGCD(FirstNumber, SecondNumber);
    printf("\nThe GCD of %d and %d is: %d\n\n", FirstNumber, SecondNumber, GCD);

    return 0;
}

int Factorial(int Number){
    int Result = 0;

    if(Number == 0)
        Result = 1;
    else
        Result = Number*Factorial(Number-1);

    return Result;
}

void UpAndDown(int Number){
    printf("Level %d: n location %p\n", Number, &Number);
    if(Number<4)
        UpAndDown(Number+1);
    printf("LEVEL %d: n location %p\n", Number, &Number);
}

int SumOfRange(int Number){
    int Result = 0;

    if (Number == 1)
        return 1;
    else
        Result = Number + SumOfRange(Number - 1);

    return Result;
}

char *ReverseFunction(char *String){
    static int Index = 0;
    static char Reverse[100];

    if(*String){
        ReverseFunction(String + 1);
        Reverse[Index++] = *String;
    }

    return Reverse;
}

int FindGCD(int FirstNumber, int SecondNumber){

   while(FirstNumber != SecondNumber) {
      if (FirstNumber > SecondNumber)
        return FindGCD(FirstNumber-SecondNumber, SecondNumber);
      else
        return FindGCD(FirstNumber, SecondNumber-FirstNumber);
   }

   return FirstNumber;
}
