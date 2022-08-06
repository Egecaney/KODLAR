#include <msp430.h> 

#define GREEN_LED 0x0001      // P1.0 is the Green LED
#define RED_LED 0x040         // P1.6 is the Red LED
#define LED_OFF 0x0000;       // LEDs OFF
#define ACLK 0x0100           // Timer_A ACLK source
#define UP 0x0010             // Timer_A UP mode (In UP mode, timers count from 0 to the value you store in TA0CCR0)


/**
 * main.c
 */

int main(void){
	WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer
	unsigned char Intervals=0;                // Count number of 50,000 counts

	P1SEL = 0x0000;                           // Enable inputs and outputs

	TA0CCR0 = 50000;                          // We will count up from 0 to 50,000
	TA0CTL = ACLK | UP;                       // Use ACLK, for UP mode  (TA0CTL = 0x0100 OR 0x0010 = 0x0110)

	P1DIR = GREEN_LED;                        // Set Green LED as an output
	P1OUT = LED_OFF;                          // Starts with LED OFF.
	
	while(1){                                 // If the timer has reached the value you moved into TA0CCR0
	    if(TA0CTL & TAIFG){                   // If timer has counted to 50,000  (0x0110 AND 0x001 = 0x0000)
	        Intervals = Intervals + 1;        // Update number of 50,000 counts
	        TA0CTL = TA0CTL & (~TAIFG);       // Count again                     (TA0CTL = 0x0000 AND 0x0001 )
	        if(Intervals == 16){              // If counted 10*50,000 = 500,000
	            Intervals = 0;                // Reset interval count
	            P1OUT = P1OUT^GREEN_LED;      // Then, toggle Green P1.0 LED     (Turn On - Turn OFF)
	        }
	    }
	}
}


/*
 * Below, we list the TA0CTL bits that we will be using, their “code names,” and their assigned functions.
 * Bits    0       Timer_A Interrupt FlaG (TAIFG)    (This bit will go HI when the timer has counted up to its specified value. It will remain LO if the timer has not finished counting yet.)
 * Bits   4-5      Mode Control (MC)                 (These two bits are used to put the peripheral into UP mode. This allows the peripheral to count up from 0 to a value you will choose)
 * Bits   8-9      Timer A Source SELect (TASSEL)    These two bits are used to specify how fast we want the timer to count.
 *
 *  Timer A0 ConTroL register (TA0CTL)
 *  Bit15-Bit10 NOT USED
 *  Bit9-Bit8   TASSEL
 *  Bit7-Bit6   NOT USED
 *  Bit5-Bit4   MC
 *  Bit3-Bit1   NOT USED
 *  Bit0        TAIFG
 *
 *  To put the Timer_A0 peripheral into UP mode, we make the MC bits 01B
 *  #define UP 0x0010 // That is 0000 0000 0001 0000 in binary
 *
 *  To specify how fast the timer will count, we will also make the TASSEL bits 01B. This tells the counter to use something called the Auxiliary CLocK (ACLK) as its timing source.
 *  With the ACLK timing source, your Timer_A0 peripheral will be counting (or incrementing) approximately once every 25 microseconds (or 25µs).
 *  #define ACLK 0x0100 // That is: 0000 0001 0000 0000 in binary
 *
 *  We can now use our two #define statements to setup and start the Timer_A0 peripheral counting:
 *  TA0CTL = ACLK | UP; // TA0CTL = 0x0110
 *
 *  Now that we have told the timer we want it to count UP and how fast we want it to count, about the only thing left to do is tell the peripheral how high to count.
 *  For now, we are going to load a value of 20,000 decimal into TA0CCRO. This will cause your timer to count for approximately 0.5 seconds.
 *  TA0CCR0 = 20000 // Count for 20,000 x 25microseconds ((20000)(25us) = 0.5 seconds)
 *
 */
