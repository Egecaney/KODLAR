#include <msp430.h> 
unsigned int i ;
/**
 * main.c
 */

int main(void){
                                    // WatchDog Timer ControL Register = WDTCTL
	WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer (WDTPW | WDTHOLD = 0x5A80)

	P1SEL = 0x0000;                 // P1 became GPIO. (PM5CTL0 = 0xFFFE Prepare pins for I/O usage)
	P1DIR = (BIT0+BIT6);            // P1.0 and P1.6 pins are OUTPUT. (01000001)

	P1DIR &=~ BIT3;                 // Configure P1.3 as INPUT.

	P1REN |= BIT3;                  // Button needs a PULLDOWN RESISTOR.
	P1OUT |= BIT3;                  // P1.3 will be 1

	P1OUT &=~ (BIT0+BIT6);          // Clear any output voltage at P1.0(LED GREEN) and P1.6(LED RED)
	                                // ~(BIT0) = 1111 1110 , ~(BIT0+BIT6) = 1011 1110
	
	while(1){
	    if(P1IN&BIT3){              // WHEN I DON'T PRESS THE BUTTON (P1.3 == 1)
            P1OUT &=~BIT6;          // Turn off the Red LED
	        P1OUT |= BIT0;          // Turn on the Green LED
	    }
	    if(!(P1IN&BIT3)){           // WHEN I PRESS THE BUTTON (P1.3 == 0)
            P1OUT &=~BIT0;          // Turn off the Green LED
	        P1OUT |= BIT6;          // Turn on the Red LED
	    }
	}
}
