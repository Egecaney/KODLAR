#include <stdio.h>
#include "malloc.h"

/*
 *  The restrict type qualifier is an optimization hint for the compiler the compiler can choose to ignore it.
 *  The restrict type qualifier is not supported by C++ .
 *  
 *  Used in pointer declarations as a type qualifier for pointers
 *      Tells the compiler that a particular pointer is the only refernce to the value it points to throughout its scope    
 *          - The same value is not referenced by any other pointer or variable within that scope
 *          - The pointer is the sole initial means of accessing a data object
 *      Tells the compiler it dpes not need to add any additional checks
 * 
 *  Without the restrict keyword, the compiler has to assume the worse case
 *      That some identifier might have changed the data in between two uses of a pointer
 * 
 *  int *restrict APtr;
 *  int *restrict BPtr;
 *  Tells the compiler that, for the duration of the scope in which APtr and BPtr are defined. They will never access the same value.
 *  Their use for pointing to integers inside an array is mutually exclusive. (Birbirini dışlayan)
 * 
 *  EXAMPLE
 *  int Array[10] = = {0,1,2,3,4,5,6,7,8,9};;
 *  int *restrict ReStar = (int*)malloc(10*sizeof(int));
 *  int *Par = Array;
 *  for(int Index=0; Index<10; Index++){
 *      Par[Index]    += 5;
 *      ReStar[Index] += 5;
 *      Array[Index]  *= 2;
 *      Par[Index]    += 3;
 *      ReStar[Index] += 5;
 *  }
 * 
 *  When it goes to compile this code and generates an assembly language, it can replace those two statements with just a single statement. (Like one line ReStar[Index] += 8;)
 * 
 * */

#define SizeOfArray 10

int main() {
    int Array[SizeOfArray] = {0,1,2,3,4,5,6,7,8,9};
    int *restrict ReStar = (int*)malloc(SizeOfArray*sizeof(int));
    int *Par = Array;

    for(int Index = 0;Index<SizeOfArray; Index++){
        ReStar[Index] = Index;   
    }

    printf("Par: %d, ReStar: %d, Array: %d\n\n", Par[0], ReStar[0], Array[0]);
    
    for(int Index=0; Index<SizeOfArray; Index++){
        Par[Index]    += ReStar[Index];
        printf("Par[%d]: %d, ReStar[%d]: %d, Array[%d]: %d\n", Index, Par[Index], Index, ReStar[Index], Index, Array[Index]);
        ReStar[Index] += 5;
        printf("Par[%d]: %d, ReStar[%d]: %d, Array[%d]: %d\n", Index, Par[Index], Index, ReStar[Index], Index, Array[Index]);
        Array[Index]  *= 2;
        printf("Par[%d]: %d, ReStar[%d]: %d, Array[%d]: %d\n", Index, Par[Index], Index, ReStar[Index], Index, Array[Index]);
        Par[Index]    += ReStar[Index];
        printf("Par[%d]: %d, ReStar[%d]: %d, Array[%d]: %d\n", Index, Par[Index], Index, ReStar[Index], Index, Array[Index]);
        ReStar[Index] += 5;
        printf("Par[%d]: %d, ReStar[%d]: %d, Array[%d]: %d\n\n", Index, Par[Index], Index, ReStar[Index], Index, Array[Index]);
    }
    
}
