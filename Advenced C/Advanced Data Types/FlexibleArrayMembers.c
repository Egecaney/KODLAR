#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

/* This code is working on the Programiz Online C Compiler but isn't working on the Visual Code. */

/* 
 *  When using a structure, we can declare an array without a dimension and whose size is flexible in nature
 *      - A flexible array member's size is variable (can be changed at the runtime)
 *  A flexible array member is declared by specifying empty square brackets ([])
 * 
 *          void *malloc (size_t NumberOfByte);
 *          void  free   (void *Ptr);
 *          void *calloc (size_t Number, size_t SizeofByte);
 *          void *realloc(void *Ptr, size_t NumberOfByte);
 * 
 */

struct StructureArray{
    int ArraySize;
    int Array[];
};

int* IntegerPointer(int DesiredSize);
char* CharacterPointer(int DesiredSize);
struct StructureArray* StructurePointer(int DesiredSize);
void ShowValues(int *IntPtr, char *ChaPtr, struct StructureArray *SPtr, int DesiredSize);

int main(void){

    int DesiredSize = 0;
    
    printf("\nEnter the DesiredSize: ");
    scanf("%d", &DesiredSize);

    int *IntPtr = IntegerPointer(DesiredSize);
    char *ChaPtr = CharacterPointer(DesiredSize);
    struct StructureArray *SPtr = StructurePointer(DesiredSize);

    printf("\nStep 1");
    ShowValues(IntPtr, ChaPtr, SPtr, DesiredSize);
    printf("\n\nStep 2 (free(IntPtr))");
    free(IntPtr);
    ShowValues(IntPtr, ChaPtr, SPtr, DesiredSize);
    printf("\n\nStep 3 (free(ChaPtr))");
    free(ChaPtr);
    ShowValues(IntPtr, ChaPtr, SPtr, DesiredSize);
    printf("\n\nStep 4 (free(SPtr))");
    free(SPtr);
    ShowValues(IntPtr, ChaPtr, SPtr, DesiredSize);

    return(0);
}

int* IntegerPointer(int DesiredSize){
    int *IntPtr;
    IntPtr = (int*)malloc((DesiredSize * sizeof(int)));

    printf("\nSize of IntPtr Malloc ((DesiredSize * sizeof(int))): %d\n", (DesiredSize * sizeof(int)));
    printf("Addresses IntPtr: %p\n", IntPtr);

    for(int Index = 0; Index<DesiredSize; Index++) {
        IntPtr[Index] = Index + 1;
    }
    return IntPtr;
    
}

char* CharacterPointer(int DesiredSize){
    char *ChaPtr;
    ChaPtr = (char*)malloc((DesiredSize * sizeof(char)));

    printf("\nSize of ChaPtr (DesiredSize * sizeof(char)): %d\n", (DesiredSize * sizeof(char)));
    printf("Addresses ChaPtr: %p\n", ChaPtr);
    
    for(int Index = 0; Index<DesiredSize; Index++) {
        ChaPtr[Index] = 'A'+Index;
    }
    
    return ChaPtr;
}

struct StructureArray* StructurePointer(int DesiredSize){
    struct StructureArray *SPtr;
    SPtr   = malloc(sizeof(struct StructureArray) + (DesiredSize * sizeof(int)));

    printf("\nSize of SPtr Malloc (sizeof(struct StructureArray) + (DesiredSize * sizeof(int))): %d\n", sizeof(struct StructureArray) + (DesiredSize * sizeof(int)));
    printf("Addresses SPtr: %p\n", SPtr);

    SPtr->ArraySize = DesiredSize;
    for(int Index = 0; Index<DesiredSize; Index++) {
        SPtr->Array[Index] = 0x01 << Index;
    }

    return SPtr;
}

void ShowValues(int *IntPtr, char *ChaPtr, struct StructureArray *SPtr, int DesiredSize){

    printf("\nThe elements of the IntPtr are: ");
    for(int Index = 0; Index<DesiredSize; Index++) {
        printf("%d ", IntPtr[Index]);
    }
    printf("\nThe elements of the ChaPtr are: %s", ChaPtr);
    printf("\nThe elements of the SPtr are  : ");
    for(int Index = 0; Index<DesiredSize; Index++) {
        printf("%d ", SPtr->Array[Index]);
    }

}
