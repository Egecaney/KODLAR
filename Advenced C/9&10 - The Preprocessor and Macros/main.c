#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define Warning(...)                                fprintf(stderr, __VA_ARGS__)

#define PrintTheFloattingValue(Message, Value)      printf("%s: %.2lf\n", Message, Value)
#define PrintTheValue(Message, Value)               printf("%s: 0x%X\n", Message, Value)
#define PrintTheOnlyMessage(Message)                printf("%s\n", Message)

#define PI                                          3.14
#define CIRCLE_AREA(Radius)                         (PI*Radius*Radius)

#define IS_Upper(Character)                         (Character >= 'A' && Character <= 'Z')
#define IS_Lower(Character)                         (Character >= 'a' && Character <= 'z')
#define IS_Alphabet(Character)                      (IS_LOWER(Character) || IS_UPPER(Character))
#define IS_Vowel_Lower(Character)                   (Character == 'a' || Character == 'e' || Character == 'i' || Character == 'o' || Character == 'u')
#define IS_Vowel_Upper(Character)                   (Character == 'A' || Character == 'E' || Character == 'I' || Character == 'O' || Character == 'U')
#define IS_Vowel(Character)                         (IS_VOWEL_LOWER(Character) || IS_VOWEL_UPPER(Character))

#define IS_Digit(Character)                         (Character >= '0' && Character <= '9')
#define IS_Alphanumeric(Character)                  (IS_ALPHABET(Character) || IS_DIGIT(Character))

#define IS_WhiteSpace(Character)                    (Character == ' ' || Character == '\t' || Character == '\r' || Character == '\n' || Character == '\0')
#define IS_SpecialCharacters(Character)             (Character >= 32 && Character <= 127 && !IS_ALPHABET(Character) && !IS_DIGIT(Character) && !IS_WHITE_SPACE(Character))

#define SetPinOnThePort(Port, Pin)                  (Port |= (0x01 << Pin))
#define ResetPinOnThePort(Port, Pin)                (Port &= ~(0x01 << Pin))
#define TogglePinOnThePort(Port, Pin)               (Port ^= (0x01 << Pin))

#define FindTheMaxValue(Number1, Number2)           (Number1 > Number2 ? Number1 : Number2)
#define UpTo(FirstIndex, FinalIndex)                for(FirstIndex = 0; FirstIndex < FinalIndex; FirstIndex++)

int main(void){

    PrintTheFloattingValue("Area of the circle", CIRCLE_AREA(4.00));

    uint8_t Port1_Pin1_Status = 0x00;
    uint8_t Port1_Pin2_Status = 0xFF;

    PrintTheOnlyMessage("\nB7 B6 B5 B4 B3 B2 B1 B0");
    PrintTheValue("\nSet the B4 of the P1.1\nThe Value", SetPinOnThePort(Port1_Pin1_Status, 4));
    PrintTheValue("\nReset the B4 of the P1.2\nThe Value", ResetPinOnThePort(Port1_Pin2_Status, 4));

    PrintTheValue("\nToggle the B3 of the P1.1\nThe Value", TogglePinOnThePort(Port1_Pin1_Status, 3));
    PrintTheValue("\nToggle the B3 of the P1.1\nThe Value", TogglePinOnThePort(Port1_Pin1_Status, 3));

    PrintTheValue("\nFindTheMaxValue(0x0A, 0x14)", FindTheMaxValue(0x0A, 0x14));

    uint8_t FirstIndex = 0, FinalIndex = 10;
    UpTo(FirstIndex, FinalIndex){
        printf("-%d-", FirstIndex);
    }

    #if(__STDC__ == 1)
        printf("\n\nImplementation is ISO-Confirming.\n");
        printf("File is %s line is %d\n", __FILE__, __LINE__);
        printf("Program last compiled at %s on %s\n", __TIME__, __DATE__);
    #else
        printf("Implementation is not ISO-Confirming.\n");
    #endif

    char Alphabet;
    printf("\nEnter any character: ");
    Alphabet = getchar();

    if (IS_Upper(Alphabet))
        printf("'%c' is uppercase\n", Alphabet);
    else if (IS_Lower(Alphabet))
        printf("'%c' is lowercase\n", Alphabet);
    else
        printf("Entered character is not alphabet\n");

    Warning("\n%s: This program is over!\n", "Warning");

    return 0;
}
