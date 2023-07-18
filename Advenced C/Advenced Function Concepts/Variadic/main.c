#include <stdio.h>
#include <stdarg.h>
#include <math.h>

/**
  * The word variadic tells us that there is some kind of change or variation is involved
  *     the variation or change here is that we are dealing with unknown number of arguments for a function
  *
  * We typically use a variadic function when we do not know the total number of arguments that will be used for a function
  *     one single function could potentially have n number of arguments
  *     a variadic function will contribute to the flexibility of the program that you are developing
  *
  * Using a variadic function
  *     A variadic function has two parts
  *         1. Mandatory arguments
  *             - At least one is required and is the fisrt one listed
  *             - Order is very important
  *         2. Optional Arguments
  *             - Listed after mandatory arguments
  *
  *
  * Here, va_list holds the information needed by va_start, va_arg, va_end, and va_copy.
  * va_start : This enables access to variadic function argument.
  * va_arg   : This one accesses the next variadic function argument.
  * va_copy  : This makes a copy of the variadic function arguments.
  * va_end   : This ends the traversal of the variadic function arguments.
  */

double Average(double V1, double V2, ...);
double Sample_STDDEV(int Count, ...);
int    AddingNumbers(int nHowMany, ...);

int main(void){
    double V1 = 10.5, V2 = 2.5;
    int  Num1 = 6, Num2 = 5;
    long Num3 = 12L, Num4 = 20L;

    printf("Average = %.2lf\n", Average(V1, 3.5, V2, 4.5, 0.0));
    printf("Average = %.2lf\n", Average(1.0, 2.0, 0.0));
    printf("Average = %.2lf\n", Average((double)Num1, V2, (double)Num2, (double)Num3, (double)Num4, 0.0));

    printf("\nAverage = %.2lf\n", Sample_STDDEV(4, 25.0, 27.3, 26.9, 25.7));

    printf( "\n10 + 20 = %d\n", AddingNumbers(2, 10, 20));
    printf( "10 + 20 + 30 = %d\n", AddingNumbers(3, 10, 20, 30));
    printf( "10 + 20 + 30 + 40 = %d\n", AddingNumbers(4, 10, 20, 30, 40));

    return(0);
}

/** Function to calculate the average of two or more arguments */
double Average(double V1, double V2, ...){
    va_list PtrArg;                             /** Pointer for variable arguments */
    double Sum = V1 + V2;                       /** Accumulate sum of the fist two arguments */
    double Value = 0.0;                         /** Argument value */

    int Count = 2;                              /** Count of number of arguments */
    va_start(PtrArg, V2);                       /** Initialize argument pointer, And so va_start remember takes the va_list and it takes the last fixed argument parameter */

    while((Value = va_arg(PtrArg, double)) != 0.0){
        Sum += Value;
        ++Count;
    }

    va_end(PtrArg);                             /** End variable argument */
    return (Sum/Count);
}

double Sample_STDDEV(int Count, ...){
    double Sum = 0;

    va_list PtrArg1;
    va_start(PtrArg1, Count);

    va_list PtrArg2;
    va_copy(PtrArg2, PtrArg1);

    for(int Index = 0; Index < Count; ++Index){
        double Num = va_arg(PtrArg1, double);
        Sum += Num;
    }
    va_end(PtrArg1);

    double Mean = Sum/Count;
    double Sum_Square_Difference = 0;

    for(int Index = 0; Index < Count; ++Index){
        double Num = va_arg(PtrArg2, double);
        Sum_Square_Difference += (Num-Mean)*(Num-Mean);
    }
    va_end(PtrArg2);

    return(sqrt(Sum_Square_Difference/Count));
}

int AddingNumbers(int nHowMany, ...) {
   int nSum = 0;

   va_list intArgumentPointer;
   va_start(intArgumentPointer, nHowMany);

    for( int i = 0; i < nHowMany; i++ ) {
        nSum += va_arg(intArgumentPointer, int);
    }
    va_end(intArgumentPointer);

    return nSum;
}
