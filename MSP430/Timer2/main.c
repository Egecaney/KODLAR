#include <msp430.h> 

#define GREEN_LED 0x0001      // P1.0 is the Green LED
#define RED_LED 0x040         // P1.6 is the Red LED
#define LED_OFF 0x0000;       // LEDs OFF
#define ENABLE_PINS 0xFFFE    // Required to use inputs and outputs
#define ACLK 0x0100           // Timer_A ACLK source
#define UP 0x0010             // Timer_A UP mode (In UP mode, timers count from 0 to the value you store in TA0CCR0)

/**
 * main.c
 */
int main(void)
{
    unsigned char CounterT0 = 0;
    unsigned char CounterT1 = 0;

    P1SEL   = 0x0000;                         // Enable inputs and outputs

    TA0CCR0 = 400;                            // Count UP from 0 to 400 (~10ms)
    TA0CTL  = ACLK|UP;                        // Use ACLK for UP mode
    TA0CCR1 = 40000;                          // Count UP from 0 to 400 (~1000ms = 1s)
    TA1CTL  = ACLK|UP;                        // Use ACLK for UP mode

    P1DIR   = RED_LED|GREEN_LED;              // P1.0 and P1.6 pins are output. (01000001)
    while(1){

        if(TA0CTL & TAIFG){                   // IF Timer 0 has counted ~10ms
            WDTCTL = WDTPW | WDTHOLD;         // Stop Watchdog Timer
            TA0CTL = TA0CTL & (~TAIFG);       // Count Again
            CounterT0 = CounterT0 +1;         // Increment 10ms counts

            if(CounterT0 == 10){              // If ~100ms has elapsed
                CounterT0 = 0;                // Reset 10ms counter
                P1OUT = P1OUT^GREEN_LED;      // Toggle RED LED
            }
        } // End Timer 0 IF

        if(TA1CTL & TAIFG){                   // IF Timer 1 has counted 5000
            TA1CTL = TA1CTL & (~TAIFG);       // Count Again
            CounterT1 = CounterT1 +1;         // Increment 1s counts

            if(CounterT0 == 3){               // If ~3s elapsed
                CounterT0 = 0;                // Reset 1s counter
                P1OUT = P1OUT^RED_LED;        // Toggle Green LED
            }
        } // End Timer 1 IF
    }
	// return 0;
}
