#include <stdio.h>

/*
 *  1. Bit manipulation is the act of algorithmically manipulating bits or other pieces of data shorter than a word  
 *  
 *  2. Computer programming tasks that require bit manipulation include
 *      - Low-level device control
 *      - Error detection
 *      - Correction algorithms
 *      - Data compression
 *      - Encryption Algorithms
 *      - Optimization
 * 
 *  3. A bitwise operates on one or more binary numbers at the level of their individual bits
 *      Used to manipulate values for comparisons and calculations
 *      Substantially faster than division, several times faster than multiplication, and sometimes significantly faster than addition
 * 
 *  4. C offers bitwise logical operators and shift operators
 *      operate on the bits in integer values
 * 
 *  5. For the left-shift operator, the vacated bits are set to 0
 *     For the right-shift operator, the vacated bits are set to 0 if the value is unsigned 
 * 
 *  & : Binary AND Operator
 *  | : Binary OR Operator
 *  ^ : Binary XOR Operator
 *  ~ : Binary ONES Complement Operator is unary and has effect of 'flipping' bits
 * << : Binary Left Shift Operator
 * >> : Binary Right Shift Operator
 * 
 * 
 *  X = ABCD EFGH
 *  X &= ~0x01 => X &= ~(0000 0001) => X &= (1111 1110) => X = X&(1111 1110) => X = ABCD EFG0  (RESET BIT)
 *  X |= ~0xFE => X |= ~(1111 1110) => X |= (0000 0001) => X = X|(0000 0001) => X = ABCD EFG1  (SET BIT)
 *  Y = 154 (1001 1010) , ~Y = -155 (0110 0101)  !Sign Changed
 * 
 * */

long long ConvertDecimalToBinary(int Number);

int main(void){

    int FirstNumber = 0, SecondNumber = 0;
    long long Binary_FirstNumber = 0, Binary_SecondNumber = 0;

    int Decimal_FirstNumberLeftShiftResult = 0;
    int Decimal_FirstNumberRightShiftResult = 0;

    long long Binary_FirstNumberComplementResult = 0;
    long long Binary_SecondNumberComplementResult = 0;
    long long Binary_FirstNumberANDSecondNumberResult = 0;
    long long Binary_FirstNumberORSecondNumberResult = 0;
    long long Binary_FirstNumberXORSecondNumberResult = 0;
    long long Binary_FirstNumberLeftShiftResult = 0;
    long long Binary_FirstNumberRightShiftResult = 0;

    /* Input number from user */
    printf("\nEnter an integer: ");
    scanf("%d", &FirstNumber);

    /* Input bit position you want to set */
    printf("Enter another integer: ");
    scanf("%d", &SecondNumber);

    Binary_FirstNumber = ConvertDecimalToBinary(FirstNumber);
    Binary_SecondNumber = ConvertDecimalToBinary(SecondNumber);

    Decimal_FirstNumberLeftShiftResult = FirstNumber << 2;
    Decimal_FirstNumberRightShiftResult = FirstNumber >> 2;

    Binary_FirstNumberComplementResult = ConvertDecimalToBinary(~FirstNumber);
    Binary_SecondNumberComplementResult = ConvertDecimalToBinary(~SecondNumber);
    Binary_FirstNumberANDSecondNumberResult = ConvertDecimalToBinary(FirstNumber & SecondNumber);
    Binary_FirstNumberORSecondNumberResult = ConvertDecimalToBinary(FirstNumber | SecondNumber);
    Binary_FirstNumberXORSecondNumberResult = ConvertDecimalToBinary(FirstNumber ^ SecondNumber);
    Binary_FirstNumberLeftShiftResult = ConvertDecimalToBinary(FirstNumber << 2);
    Binary_FirstNumberRightShiftResult = ConvertDecimalToBinary(FirstNumber >> 2);

    printf("The result of applying the ~ operator on number %d (%lld) is: %lld \n", FirstNumber, Binary_FirstNumber, Binary_FirstNumberComplementResult);
    printf("The result of applying the ~ operator on number %d (%lld) is: %lld \n", SecondNumber, Binary_SecondNumber, Binary_SecondNumberComplementResult);
    printf("The result of applying the & operator on number %d (%lld) and number %d (%lld) is: %lld \n", FirstNumber, Binary_FirstNumber, SecondNumber, Binary_SecondNumber, Binary_FirstNumberANDSecondNumberResult);
    printf("The result of applying the | operator on number %d (%lld) and number %d (%lld) is: %lld \n", FirstNumber, Binary_FirstNumber, SecondNumber, Binary_SecondNumber, Binary_FirstNumberORSecondNumberResult);
    printf("The result of applying the ^ operator on number %d (%lld) and number %d (%lld) is: %lld \n", FirstNumber, Binary_FirstNumber, SecondNumber, Binary_SecondNumber, Binary_FirstNumberXORSecondNumberResult);
    printf("The result of applying the left shift operator << on number %d (%lld) by 2 places is number %d (%lld)\n", FirstNumber, Binary_FirstNumber, Decimal_FirstNumberLeftShiftResult, Binary_FirstNumberLeftShiftResult);
    printf("The result of applying the right shift operator >> on number %d (%lld) by 2 places is number %d (%lld)\n\n", FirstNumber, Binary_FirstNumber, Decimal_FirstNumberRightShiftResult, Binary_FirstNumberRightShiftResult);
    
    return (0);
}

long long ConvertDecimalToBinary(int Number){
    long long BinaryNumber = 0;
    int Remainder, i = 1;
    while (Number!=0){
        Remainder = Number%2;
        Number /= 2;
        BinaryNumber += Remainder*i;
        i *= 10;
    }
    return BinaryNumber;
}