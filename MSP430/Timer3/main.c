#include <msp430.h> 

#define GreenLed 0x0001    // P1.0 is the Green LED
#define RedLed   0x0040    // P1.6 is the Red LED
#define ACLK     0x0100    // Timer_A ACLK Source
#define UP       0x0010    // Timer_A UP Mode


int main(void){

    unsigned char Intervals=0;  // Count number of 40000 counts
	WDTCTL = WDTPW | WDTHOLD;	// Stop Watchdog Timer

	P1SEL = 0x0000;             // Enable inputs and outputs

	TA0CCR0 = 40000;            // We will count up from 0 to 40000
	TA0CTL  = ACLK|UP;          // Use ACLK, for UP Mode (0x0110)

	P1DIR = GreenLed+RedLed;    //Set Red and Green LED as an output
	P1OUT = GreenLed;
	
	while(1){

	    if(TA0CTL & TAIFG){                  // If timer has counted to 40,000
	        TA0CTL = TA0CTL & (~TAIFG);      // Count Again
	        Intervals = Intervals+1;         // Update number of 40,000 counts

	        if(P1OUT & GreenLed){            // If the red LED is on
	            if(Intervals == 3){          // Have 3*40,000 counts gone by?
	                P1OUT = RedLed;          // If yes, turn on RED LED
	                Intervals = 0;           //  Clear number of 40,000 counts
	            }
	        }
	        else{                            // Else, red LED is off
	            P1OUT = GreenLed;            //  Turn on the Green LED
	            Intervals = 0;               // Clear number of 40,000 counts
	        }

	    }
	}
}
