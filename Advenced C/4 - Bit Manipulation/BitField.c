#include <stdio.h>
#include <stdbool.h>   //C99, defines bool, true, false

/*
 *  We understand that you can perform all sorts of sophisticated operations on bits
 *      Often performed on data items that contain packed information
 *  
 *  You can pack information into the bits of a byte if you do not need to use the entire byte to represent the data
 *      flags that are used for boolean true or false condition can be represented in a single bit on a computer
 * 
 *  You can use bit field in a structure to address individual bits or groups of bits in a value
 *  Bit field enable better memory utilization by sorting data in the minimum number of bits required
 *      format enables you to allocate a specified number of bits for a data item
 *      can easily set and retrieve its value without having to use masking and shifting
 * 
 *  A bit field is declared by following an unsigned int member name with a colon (:)
 *      An integer constant is placed after the colon which represents the width of the field
 *          The number of bits in which the member is stored
 * 
 *  Bit-Field members of structures are accessed exactly as any other structure member 
 *
 * */

/* Line Styles */
#define SOLID   0
#define DOTTED  1
#define DASHED  2

/* Primary Colors */
#define BLUE    4
#define GREEN   2
#define RED     1

/* Mixed Colors */
#define BLACK   0
#define YELLOW  (RED | GREEN)
#define MAGENTA (RED | BLUE)
#define CYAN    (GREEN | BLUE)
#define WHITE   (RED | GREEN | BLUE)

const char * Colors[8] = {"Black", "Red", "Green", "Yellow",   "Blue", "Magenta", "Cyan", "White"};

struct BoxProps {
    bool Opaque                 : 1;  // or unsigned int (pre C99)
    unsigned int FillColor      : 3;
    unsigned int                : 4;
    bool ShowBorder             : 1;  // or unsigned int (pre C99)
    unsigned int BorderColor    : 3;
    unsigned int BorderStyle    : 2;
    unsigned int                : 2;
};

void ShowSettings(const struct BoxProps *BoxPropsPtr);

int main(void) {
    
    struct BoxProps Box = {true, YELLOW, true, GREEN, DASHED};

    printf("\nOriginal Box Settings:\n");
    ShowSettings(&Box);

    Box.Opaque = false;
    Box.FillColor = WHITE;
    Box.BorderColor = MAGENTA;
    Box.BorderStyle = SOLID;
    printf("Modified Box Settings:\n");
    ShowSettings(&Box);

    return 0;
}

void ShowSettings(const struct BoxProps *BoxPropsPtr){

    printf("Box is %s.\n", BoxPropsPtr->Opaque == true ? "Opaque":"Transparent");
    printf("The fill color is %s.\n", Colors[BoxPropsPtr->FillColor]);
    printf("Border %s.\n", BoxPropsPtr->ShowBorder == true ? "Shown":"Not Shown");
    printf("The border color is %s.\n", Colors[BoxPropsPtr->BorderColor]);
    printf("The border style is ");

    switch (BoxPropsPtr->BorderStyle){
        case SOLID  : printf("SOLID.\n\n"); break;
        case DOTTED : printf("DOTTED.\n\n"); break;
        case DASHED : printf("DASHED.\n\n"); break;
        default     : printf("unknown type.\n\n"); break;
    }

}