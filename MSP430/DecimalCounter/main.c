#include <msp430.h>
unsigned int FirstDecimal = 0;
unsigned int SecondDecimal = 0;
unsigned int ThirdDecimal = 0;
unsigned int ForthDecimal = 0;
unsigned int Delay,i1,i2;

/*
// Define Pin Mapping of 7-segment Display
#define SEG_A   BIT0
#define SEG_B   BIT1
#define SEG_C   BIT2
#define SEG_D   BIT3
#define SEG_E   BIT4
#define SEG_F   BIT5
#define SEG_G   BIT6

// Define each digit according to truth table
#define D0  (SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F)
#define D1  (SEG_B + SEG_C)
#define D2  (SEG_A + SEG_B + SEG_D + SEG_E + SEG_G)
#define D3  (SEG_A + SEG_B + SEG_C + SEG_D + SEG_G)
#define D4  (SEG_B + SEG_C + SEG_F + SEG_G)
#define D5  (SEG_A + SEG_C + SEG_D + SEG_F + SEG_G)
#define D6  (SEG_A + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
#define D7  (SEG_A + SEG_B + SEG_C)
#define D8  (SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
#define D9  (SEG_A + SEG_B + SEG_C + SEG_D + SEG_F + SEG_G)

const unsigned int Numbers[10] = {D0, D1, D2, D3, D4, D5, D6, D7, D8, D9};
*/

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1SEL=0x00;
    P1DIR=0xFF;
    P2SEL=0x00;
    P2DIR=0xFF;

    while(1){
        for(ThirdDecimal=0;ThirdDecimal<10;ThirdDecimal++){
            for(SecondDecimal=0;SecondDecimal<10;SecondDecimal++){
                  for(FirstDecimal=0;FirstDecimal<10;FirstDecimal++){
                      for(i2=0;i2<10;i2++){
                          PinNumbers(2);
                          Numbers(ThirdDecimal);
                          for(Delay=0;Delay<500;Delay++){
                          }
                          PinNumbers(3);
                          Numbers(SecondDecimal);
                          for(Delay=0;Delay<500;Delay++){
                          }
                          PinNumbers(4);
                          Numbers(FirstDecimal);
                          for(Delay=0;Delay<500;Delay++){
                          }
                      }
                  }
            }
        }
    }
}


void Numbers(int Number){

    if(Number == 0){
        P1OUT &=~ BIT0;     // A
        P1OUT &=~ BIT1;     // B
        P1OUT &=~ BIT7;     // C
        P1OUT &=~ BIT3;     // D
        P1OUT &=~ BIT4;     // E
        P1OUT &=~ BIT5;     // F
        P1OUT |=  BIT6;     // G
    }
    else if(Number == 1){
        P1OUT |=  BIT0;     // A
        P1OUT &=~ BIT1;     // B
        P1OUT &=~ BIT7;     // C
        P1OUT |=  BIT3;     // D
        P1OUT |=  BIT4;     // E
        P1OUT |=  BIT5;     // F
        P1OUT |=  BIT6;     // G
    }
    else if(Number == 2){
        P1OUT &=~ BIT0;      // A
        P1OUT &=~ BIT1;      // B
        P1OUT |=  BIT7;      // C
        P1OUT &=~ BIT3;      // D
        P1OUT &=~ BIT4;      // E
        P1OUT |=  BIT5;      // F
        P1OUT &=~ BIT6;      // G
    }
    else if(Number == 3){
        P1OUT &=~ BIT0;      // A
        P1OUT &=~ BIT1;      // B
        P1OUT &=~ BIT7;      // C
        P1OUT &=~ BIT3;      // D
        P1OUT |=  BIT4;      // E
        P1OUT |=  BIT5;      // F
        P1OUT &=~ BIT6;      // G
    }
    else if(Number == 4){
        P1OUT |=  BIT0;      // A
        P1OUT &=~ BIT1;      // B
        P1OUT &=~ BIT7;      // C
        P1OUT |=  BIT3;      // D
        P1OUT |=  BIT4;      // E
        P1OUT &=~ BIT5;      // F
        P1OUT &=~ BIT6;      // G
    }
    else if(Number == 5){
        P1OUT &=~ BIT0;      // A
        P1OUT |=  BIT1;      // B
        P1OUT &=~ BIT7;      // C
        P1OUT &=~ BIT3;      // D
        P1OUT |=  BIT4;      // E
        P1OUT &=~ BIT5;      // F
        P1OUT &=~ BIT6;      // G
    }
    else if(Number == 6){
        P1OUT &=~ BIT0;      // A
        P1OUT |=  BIT1;      // B
        P1OUT &=~ BIT7;      // C
        P1OUT &=~ BIT3;      // D
        P1OUT &=~ BIT4;      // E
        P1OUT &=~ BIT5;      // F
        P1OUT &=~ BIT6;      // G
    }
    else if(Number == 7){
        P1OUT &=~ BIT0;      // A
        P1OUT &=~ BIT1;      // B
        P1OUT &=~ BIT7;      // C
        P1OUT |=  BIT3;      // D
        P1OUT |=  BIT4;      // E
        P1OUT |=  BIT5;      // F
        P1OUT |=  BIT6;      // G
    }
    else if(Number == 8){
        P1OUT &=~ BIT0;      // A
        P1OUT &=~ BIT1;      // B
        P1OUT &=~ BIT7;      // C
        P1OUT &=~ BIT3;      // D
        P1OUT &=~ BIT4;      // E
        P1OUT &=~ BIT5;      // F
        P1OUT &=~ BIT6;      // G
    }
    else  if(Number == 9){
        P1OUT &=~ BIT0;      // A
        P1OUT &=~ BIT1;      // B
        P1OUT &=~ BIT7;      // C
        P1OUT &=~ BIT3;      // D
        P1OUT |=  BIT4;      // E
        P1OUT &=~ BIT5;      // F
        P1OUT &=~ BIT6;      // G
    }
}

void PinNumbers(int PinNumber){
    if(PinNumber == 1){
        P2OUT &=~ BIT0;     // Diode 4
        P2OUT &=~ BIT1;     // Diode 3
        P2OUT &=~ BIT2;     // Diode 2
        P2OUT |=  BIT3;     // Diode 1
    }
    else if(PinNumber == 2){
        P2OUT &=~ BIT0;     // Diode 4
        P2OUT &=~ BIT1;     // Diode 3
        P2OUT |=  BIT2;     // Diode 2
        P2OUT &=~ BIT3;     // Diode 1
    }
    else if(PinNumber == 3){
         P2OUT &=~ BIT0;    // Diode 4
         P2OUT |= BIT1;     // Diode 3
         P2OUT &=~ BIT2;    // Diode 2
         P2OUT &=~ BIT3;    // Diode 1
    }
    else if(PinNumber == 4){
         P2OUT|= BIT0;      // Diode 4
         P2OUT &=~ BIT1;    // Diode 3
         P2OUT &=~ BIT2;    // Diode 2
         P2OUT &=~ BIT3;    // Diode 1
    }
}
