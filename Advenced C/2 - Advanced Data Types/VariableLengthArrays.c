#include <stdio.h>

/* 
 *  Arrays are of constant size
 *  A variable-length array is an array whose length, or size, is defined in terms of an expression evaluated at execution time
 *      - Enable you to work with arrays in your programs without having to give them a constat size
 */

typedef size_t Size;
Size globalRowSize, globalColumnSize;

void FillTheBeans2D(int (*Beans2D)[globalColumnSize], Size Rows, Size Columns);
int  Sum2D(int Beans2D[globalRowSize][globalColumnSize], Size Rows, Size Columns);
void FillTheCharArray(char *Alphabetic, Size NumberOfCharacters);

int main(void){

    Size sizeArrayRows = 0, sizeArrayColumns = 0, sizeArrayCharacters = 0;

    printf("\nEnter the number of rows you want to store: ");
    scanf("%zd", &sizeArrayRows);
    printf("Enter the number of columns in a row: ");
    scanf("%zd", &sizeArrayColumns);

    globalRowSize = sizeArrayRows;
    globalColumnSize = sizeArrayColumns;

    int Beans[sizeArrayRows][sizeArrayColumns];
    FillTheBeans2D(Beans, sizeArrayRows, sizeArrayColumns);

    for(int NRows = 0; NRows < sizeArrayRows; NRows++){
        for(int NColumns = 0; NColumns < sizeArrayColumns; NColumns++){
            printf("%d ", Beans[NRows][NColumns]);
        }
        printf("\n");
    }

    printf("Summation: %d\n", Sum2D(Beans, sizeArrayRows, sizeArrayColumns));

    printf("\nEnter the number of character: ");
    scanf("%zd", &sizeArrayCharacters);

    char Alphabetic[sizeArrayCharacters];
    FillTheCharArray(Alphabetic, sizeArrayCharacters);

    for(int Index = 0; Index < sizeArrayCharacters; Index++){
        printf("%c ", Alphabetic[Index]);
    }

    return(0);

}

void FillTheBeans2D(int (*Beans2D)[globalColumnSize], Size Rows, Size Columns){
    for(int NRows = 0; NRows < Rows; NRows++){
        for(int NColumns = 0; NColumns < Columns; NColumns++){
            *(*(Beans2D + NRows) + NColumns) = (int)(NRows + NColumns);
        }
    }
}

int Sum2D(int Beans2D[globalRowSize][globalColumnSize], Size Rows, Size Columns){
    int Total = 0;
    for(int NRows = 0; NRows < Rows; NRows++){
        for(int NColumns = 0; NColumns < Columns; NColumns++){
            Total += Beans2D[NRows][NColumns];
        }
    }
    return Total;
}

void FillTheCharArray(char *Alphabetic, Size NumberOfCharacters){
    for(int Index = 0; Index < NumberOfCharacters; Index++){
            *(Alphabetic + Index)= 'A' + Index;
    }
}
