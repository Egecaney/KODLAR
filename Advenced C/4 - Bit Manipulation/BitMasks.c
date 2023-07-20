#include <stdio.h>

/*
 *  A bit mask is data that is used for bitwise operations
 *      A bit pattern with some bits set to on (1) and some bits to off (0)
 * 
 *  A mask can be used to set multiple bits in a byte to either on, off or inverted from on to off (or vice versa) using a single bitwise operator
 *  
 *  Imagine you want to create a program that holds a state, which is based on multiple values that are one(true) or zero(false)
 *      - can store these values in different variables (booleans or integers)
 *      - or instead use a single integer variable and use each bit of its internal 32 bits to represent the different true and false values
 *
 *  00000101
 *      - The first bit (reading from right ro left) is true, which represent the first variable
 *      - The 2nd is false, which represents the 2nd variable. The 3rd true. And so on. 
 *      ! A VERY EFFICIENT WAY OF STORONG DATA AND HAS MANY USAGES
 * 
 *  Mask  = 00000010
 *  Flags = ABCDEFGH
 *      Flags = Flags & Mask  = ABCDEFGH & 00000010 = 000000G0      (Check Flag (Revealing the relevant bit))
 *      Flags = Flags | Mask  = ABCDEFGH | 00000010 = ABCDEF1H      (Turning Bits ON (Setting   bits))
 *      Flags &= ~Mask        = ABCDEFGH & 11111101 = ABCDEF0H      (Turning Bits OFF (Clearing Bits))
 *      Flags = Flags ^ Mask  = ABCDEFGH ^ 00000010 = ABCDEFG'H     (Toggling Bits)
 * 
 *  unsigned int PackedData;
 *  (Unused (31:29))(F1 (28))(F2 (27))(F3 (26))(Type (25:18))(Index        (17:0))
 *         101          1       0         1       10101010     100110011001100110
 * 
 *  unsigned int Index  = (PackedData & 0x0003FFFF) >> 0;
 *  unsigned int Type   = (PackedData & 0x03FC0000) >> 18;
 *  unsigned int F3     = (PackedData & 0x04000000) >> 26;
 *  unsigned int F2     = (PackedData & 0x08000000) >> 27;
 *  unsigned int F1     = (PackedData & 0x10000000) >> 28;
 *  unsigned int Unused = (PackedData & 0xE0000000) >> 29;
 * 
 * */

int main() {
    int Number, Position, NewNumber, BitStatus;

    /* Input number from user */
    printf("\nEnter any number: ");
    scanf("%d", &Number);

    /* Input bit Position you want to set */
    printf("Enter nth bit to check and set (0-31): ");
    scanf("%d", &Position);

    /* Right shift Number, Position times and perform bitwise AND with 1 */
    BitStatus = (Number >> Position) & 1;
    printf("The %d bit is set to %d\n", Position, BitStatus);

    /* Left shift 1, n times and perform bitwise OR with num */
    NewNumber = (1 << Position) | Number;
    printf("\nBit set successfully.\n\n");

    printf("Number before setting %d bit: %d (in decimal)\n", Position, Number);
    printf("Number after setting %d bit: %d (in decimal)\n\n", Position, NewNumber);

    return 0;
}