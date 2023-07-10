#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "stdbool.h"

/*
 *  A binary number is a number that includes only ones and zeros, the number could be any length.
 *  A byte consists of eight smaller units called bits. Each 1 and 0 in a binary number represents 1 bit
 *  
 *  The rightmost bit of a byte is known as the least significant or low-order-bit, whereas the leftmost bit is known as the most significant or high-order bit.
 *  Changing a bit's value to 1 is referred to as setting the bit
 *  Changing a bit's value to 0 is referred to as resetting a bit
 * 
 *  BIT         _Bool           1                 0 to 1       
 *  Byte        char            8              -128 to 127                             
 *  Word        short int       16           -32768 to 32767
 *  Long        long int        32      -2147483648 to 2147483647
 * 
 *  Negative Numbers:
 *  Computers represent such numbers using a "twos complement" notation
 *      The leftmost bit represents the sign bit
 *          - If the bit is 1, the number is negative
 *          - If the bit is 0, the number is positive 
 *  To convert -5 to binary, 1 is added, which gives -4
 *  4 expressed in binary is         0000 0100 (+4)
 *  Complementing the bits produces  1111 1011 (-5)
 * 
 *  A hardware device is often controlled by sending it a byte or two in which each bit has a particular meaning.
 *  Operating System information about files often is stored by using particular bits to indicate particular items.
 *  Many compression and encryption operations manipulate individual bits.
 * 
 * */

void ConverttoDecimalToBinary(int Decimal);
void ConvertBinaryToDecimal(long long Binary);

int main(){

    int DTB_DecimalNumber = 0, BTD_DecimalNumber = 0;
    long long BTD_BinaryNumber = 0;
    int ConversionSelection = 0;
    bool OperationStatus = true;

    printf("\nWrite '1' Decimal to Binary\nWrite '2' Binary to Decimal\nEnter the conversion selection: ");
    scanf("%d", &ConversionSelection);

    while(OperationStatus == true){
        switch(ConversionSelection){
            case 1:
                printf("\nEnter a Decimal Number: ");
                scanf("%d", &DTB_DecimalNumber);
                ConverttoDecimalToBinary(DTB_DecimalNumber);
            break;
            case 2:
                printf("\nEnter a Binary Number: ");
                scanf("%lld", &BTD_BinaryNumber);
                ConvertBinaryToDecimal(BTD_BinaryNumber);    
            break;
        }
    
        printf("\nWrite '1' Decimal to Binary\nWrite '2' Binary to Decimal\nWrite '3' Finish the operation\nEnter the conversion selection: ");
        scanf("%d", &ConversionSelection);
        if(ConversionSelection == 3){
            printf("The program is finished!\n\n");
            OperationStatus = false;
        }   
    }
    return(0);
}

void ConverttoDecimalToBinary(int Decimal){
    long long BinaryNumber = 0;
    int Remainder, i = 1, LastBitPlace = 0, TempDecimal = Decimal;

    while(TempDecimal != 0) {
        Remainder = TempDecimal % 2;
        TempDecimal   = TempDecimal / 2;
        BinaryNumber += Remainder * i;
        i = i * 10;
        LastBitPlace++;
    }

    if(Decimal < 0){
        int BitNumbersArray[LastBitPlace];
        int Power = 1;
        long long TempBinaryNumber = abs(BinaryNumber)-1;
        BinaryNumber = 0;
        for(int Index = 0; Index < LastBitPlace; Index++){
            BitNumbersArray[Index] = (((TempBinaryNumber/Power)&0x01)^0x01);
            BinaryNumber += BitNumbersArray[Index]*Power;
            Power *= 10;
        }
        printf("%d in Decimal = Sign Bit(1)0%lld to Binary\n", Decimal , BinaryNumber);
    }
    else{
        printf("%d in Decimal = Sign Bit(0)%lld to Binary\n", Decimal , BinaryNumber);
    }
}

void ConvertBinaryToDecimal(long long Binary) {
    int DecimalNumber = 0, i = 0, Remainder;
    long long TempBinary = Binary;
    while (TempBinary!=0)    {
        Remainder = TempBinary % 10;
        TempBinary /= 10;
        DecimalNumber += Remainder*pow(2,i);
        ++i;
    }
    printf("%lld in Binary = %d in Decimal\n", Binary, DecimalNumber);
}