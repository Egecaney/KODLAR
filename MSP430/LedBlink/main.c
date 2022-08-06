#include <msp430.h> 

#define GREEN_ON 0x0001;    // P1.0 Led GREEN
#define RED_ON   0x0040;    // P1.6 Led RED
#define LED_OFF  0x0000;    // LEDs OFF
#define LED_BOTH 0x0041;    // LEDs ON
unsigned int i;

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer (WDTPW | WDTHOLD = 0x5A80)
    P1SEL = 0x0000;             // P1 became GPIO. (PM5CTL0 = 0xFFFE Prepare pins for I/O usage)
    P1DIR = 0x0041;             // P1.0 and P1.6 pins are output. (01000001)
    P1OUT = GREEN_ON;            // Starts with Green Led.

    while(1){
        P1OUT = P1OUT^LED_BOTH;
        __delay_cycles(1000000);    // 1s Delay
    }

    /*
    P1SEL = 0x0000;             // P1 became GPIO. (PM5CTL0 = 0xFFFE Prepare pins for I/O usage)
    P1DIR = 0x0041;             // P1.0 and P1.6 pins are output. (01000001)
    P1OUT = LED_OFF;            // Starts with LEDs OFF.

    while(1){
        for(i=0;i<50000;i++){
            P1OUT = GREEN_ON; // (00000000 XOR 00000001 = 00000001)
        }
        P1OUT = LED_OFF;
        for(i=0;i<50000;i++){
            P1OUT = RED_ON;   // (00000000 XOR 01000000 = 01000000)
        }
        P1OUT = LED_OFF;
    }
    */

    /* ALTERNATIVE SOLUTION
    P1SEL = 0x00;
    P1DIR |= BIT0;
    P1DIR |= BIT6;
    P1OUT &=~ BIT0;
    P1OUT &=~ BIT6;

    while(1){
        P1OUT |= BIT0;
        P1OUT &=~ BIT6;

        for(i=1;i<50000;i++){
        }
        P1OUT &=~ BIT0;
        P1OUT |= BIT6;
        for(i=1;i<50000;i++){
        }
    }
    // return 0;
     */
}





/*
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    asm("mov.b #00000000b,&0x026");
    asm("mov.b #01000001b,&0x022");

    asm("mov.b #01000000b,&0x021");
    __delay_cycles(1000000);
    asm("mov.b #00000001b,&0x021");
    __delay_cycles(1000000);
*/
