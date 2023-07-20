#include <stdio.h>
#include <stdint.h>

/*
 *  C supports the use of a comma that can be used in expressions as an operator
 *      - has the lowest precedence of any C operator
 *      - acts as a sequence point
 *  
 *  A binary operator that evaluates its first operand and discards the result
 *      then evaluates the second operand and returns this value (and type)
 *          because all operators in C produce a value, the value of comma operator is that of the rightmost expression
 * 
 *  The comma operator can be used to separate multiple expressions anywhere that a valid C expression can be used
 *  The comma operator exists because there are times when you d not want to separate expressions with semicolons 
 * 
 * */

int main(){

    uint8_t Number1 = (9, 10);
    printf("\nUsing comma as operator => %d\n", Number1);
    uint8_t Number2 = (Number1++, ++Number1);
    printf("Using comma as operator => %d\n", Number2);

    // Comma separating Number3 = 10 and Number4
    uint8_t Number3 = 10, Number4;
    printf("\nComma acting as operator\n");
    Number4 = (Number3++, printf("Number3 = %d\n", Number3), ++Number3,
                          printf("Number3 = %d\n", Number3), Number3++);
 
    // Note that last expression is evaluated but side effect is not updated to Number4
    printf("Number4 = %d\n", Number4);
    printf("Number3 = %d\n\n", Number3);

    for(uint8_t FirstIndex = 1, SecondIndex = 2; FirstIndex < 10 && SecondIndex < 10; FirstIndex++){
        if(FirstIndex == 5){
            FirstIndex = 6, SecondIndex = 10;  // Using comma as separator
        }
        printf("FirstIndex: %d --- SecondIndex: %d\n", FirstIndex, SecondIndex);
    }

    printf("\nFirst Line\n"),
    printf("Second Line\n"),
    printf("Third Line\n"),
    printf("Last Line\n\n");

    return 0;
}