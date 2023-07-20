#include <stdio.h>

/*
 *  Type Qualifiers can be used in front of variables to give the compiler more information about the intended use of the variable helps with OPTIMIZATION.
 *      - const, volatile and restrict
 *  
 *  Const:
 *      1. The compiler allows you to associate the const qualifier with variables have a constant value throught the program's execuation.
 *      2. If you try to assign a value to a const variable after initializing it
 *          The compiler might issue an error message, although it is not required to do so
 *      3. One of the motivations for the const attribute in the language is that it allows the compiler to place your const variables into Read-Only-Memory(ROM).
 *
 */

struct Index{int Increasing, Decreasing;};
#define PtrV4ArraySize  5

const char *MONTHS[12] = {"January, February, March, April, May, June, July, August, September, October, November, December"};
/* In the order .c file using constant, we should use like this "extern const *MONTHS[12];" */

void DisplayRandomNumbers(const int Array[], unsigned int SizeOfArray, char *Element);
void DisplayIndex(const struct Index Index, char *Element);
void DisplayIndexV4(const struct Index Index[]);                                    // For Pointer : void DisplayIndexV4(const struct Index *Index);

int main(void){

    const double    PI = 3.141592654;
    printf("\nPI: %.4f\n", PI);

    puts("\n---Constant Integer with Designated Initializers---");
    
    const int RandomNumbers[100] = {1, 2, 3, [3 ... 9] = 10, [10] = 80, 15, [70] = 50, [42] = 400};
    const int RandomNumbersV2[]  = {1, 2, 3, [3 ... 9] = 10, [10] = 80, 15, [70] = 50, [42] = 400};
    int RandomNumbersV3[]        = {1, 2, 3, [3 ... 9] = 10, [10] = 80, 15, [70] = 50, [42] = 400};
    DisplayRandomNumbers(RandomNumbers, sizeof(RandomNumbers)/sizeof(RandomNumbers[0]), "");
    DisplayRandomNumbers(RandomNumbersV2, sizeof(RandomNumbersV2)/sizeof(RandomNumbersV2[0]), "V2");
    DisplayRandomNumbers(RandomNumbersV3, sizeof(RandomNumbersV3)/sizeof(RandomNumbersV3[0]), "V3");
    
    puts("\n---Constant Structure with Designated Initializers---");

    const struct    Index Index  = {.Increasing = 2, .Decreasing = 3};
    const struct    Index IndexV2 = {Increasing : 4, Decreasing : 5};
    const struct    Index IndexV3 = {6,7};
    const struct    Index IndexV4[PtrV4ArraySize] = {[2].Decreasing = 5, [2].Increasing = 6, [0].Increasing = 2};
    DisplayIndex(Index, "");
    DisplayIndex(IndexV2, "V2");
    DisplayIndex(IndexV3, "V3");
    DisplayIndexV4(IndexV4);

    typedef const int ZIP;
    const ZIP ZipAgain = 8;
    printf("\nZIP ZipAgain = %d\n",ZipAgain);

    const float *FloatPtr;          /* FloatPtr points to a constant float value. The value of FloatPtr itself can be changed. (Same as float const *FloatPtr) */
    float *const FloatPtrV2;        /* FloatPtrV2 is a const pointer. FloatPtrV2 cannot have its value changed so that means the address can't change. */
    const float *const FloatPtrV3;  /* That basically means that the pointer must always point to the same location and that the value stored at the location must also not change. */

    return(0);

}

void DisplayRandomNumbers(const int Array[], unsigned int SizeOfArray, char *Element){
    printf("Size of RandomNumber%s = %d\n", Element, SizeOfArray);
    if(SizeOfArray == 100)
        printf("RandomNumbers%s = [0] = %d, [10] = %d, [70] = %d, [99] = %d\n", Element, Array[0], Array[10], Array[70], Array[99]);
    else
        printf("RandomNumbers%s = [0] = %d, [10] = %d, [70] = %d\n", Element, Array[0], Array[10], Array[70]);
}

void DisplayIndex(const struct Index Index, char *Element){
    printf("Index%s.Increasing = %d, Index%s.Decreasing = %d\n", Element, Index.Increasing, Element, Index.Decreasing);
}

void DisplayIndexV4(const struct Index Index[]){
    for(int Counter = 0; Counter < PtrV4ArraySize; Counter++){
        printf("IndexV4[%d].Increasing = %d, IndexV4[%d].Decreasing = %d\n", Counter, Index[Counter].Increasing, Counter, Index[Counter].Decreasing);
    }
}