#include <msp430.h> 

// I used P2 because P1.0 and P1.6 are used in board as a LEDs
#define P1  BIT0     // Charlieplex P0 -> P2.0
#define P2  BIT1     // Charlieplex P1 -> P2.1
#define P3  BIT2     // Charlieplex P3 -> P2.2
#define P4  BIT3     // Charlieplex P4 -> P2.3

// Data Table for 12 Charliplexed LEDs
const unsigned int HighInput[12] = {P1,P2,P1,P3,P1,P4,P2,P3,P2,P4,P3,P4};
const unsigned int LowOutput[12] = {P2,P1,P3,P1,P4,P1,P3,P2,P4,P2,P4,P3};
const unsigned int Z1Pins[12] = {P3,P3,P2,P2,P2,P2,P1,P1,P1,P1,P1,P1};
const unsigned int Z2Pins[12] = {P4,P4,P4,P4,P3,P3,P4,P4,P3,P3,P2,P2};

unsigned int i;

void CharliePlexing(unsigned int value){

    P2DIR &= ~(Z1Pins[value]+Z2Pins[value]);       // Set High Z Pins as Input
    P2DIR |= (LowOutput[value]+HighInput[value]);  // Set High & Low Pins as Output

    P2OUT &= ~(LowOutput[value]);                  // Set State of Low Pin
    P2OUT |= HighInput[value];                     // Set State of Low Pin

}

void main(void){

    WDTCTL = WDTPW | WDTHOLD;           // Stop Watchdog Timer
    while(1){
        for(i=0;i<12;i++){
            CharliePlexing(i);          // Switch on LED (i)
            __delay_cycles(100000);     // Delay 100 ms
        }
    }

}
