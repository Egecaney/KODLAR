#include <msp430.h>

// PRE 3.4
#define Switch   BIT3                   // Switch  -> P1.3
#define RedLed   BIT6                   // RED LED -> P1.6

void main(void){

    WDTCTL = WDTPW | WDTHOLD;           // Stop Watchdog Timer
    P1OUT = 0x00;
    P1DIR |= RedLed;                    // Set LED pin -> Output
    P1DIR &= ~Switch;                   // Set Switch pin -> Input
    P1REN |= Switch;                    // Enable Resistor for Switch pin
    P1OUT |= Switch;                    // Select Pull Up for Switch pin

    P1IES &= ~Switch;                   // Select Interrupt on Rising Edge
    P1IE |= Switch;                     // Enable Interrupt on Switch pin

    __bis_SR_register(LPM4_bits + GIE); // Enter LPM4 and Enable CPU Interrupt

}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){
    P1OUT ^= RedLed;                    // Toggle Green LED
    P1IFG &= ~Switch;                   // Clear SW interrupt flag
}
//

/* Pre 3.5
#define RedLed BIT6                     // Red LED -> P1.6
volatile unsigned int Counter = 0;
volatile unsigned int TempTACCR0 = 0;

void main(void){

    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer

    P1DIR |= RedLed;                    // Set LED pin -> Output
    P1OUT &=~ RedLed;                   // Turn OFF LED

    TACCR0 = 2000;                      // Set Timer Timeout Value
    TACCTL0 |= CCIE;                    // Enable Overflow Interrupt
    TACTL |= MC_1 + TASSEL_1 + TACLR ;  // Set Mode -> Up Count, Clock -> ACLK, Clear Timer

    __bis_SR_register(LPM3_bits + GIE); // Go to LPM3 (Only ACLK active), Enable CPU Interrupt

    while(1);

}

#pragma vector = TIMER0_A0_VECTOR       // CCR0 Interrupt Vector
__interrupt void CCR0_ISR(void){
    P1OUT ^= RedLed;                    // Toggle LED
    Counter++;
    if(Counter == 2){
        TempTACCR0 = TACCR0;
        TACCR0 += TACCR0;
        if(TempTACCR0 > TACCR0){
            TACCR0 = 2000;
        }
        Counter = 0;
    }
}*/


/* Pre 3.6
#define RedLed BIT6                     // Red LED -> P1.6
volatile int Counter = 0;

void main(void){

    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer

    P1DIR |= RedLed;                    // Set LED pin -> Output
    P1OUT &=~ RedLed;                   // Turn OFF LED

    TACCR0 = 10000;                     // Set Timer Timeout Value
    TACCTL0 |= CCIE;                    // Enable Overflow Interrupt
    TACTL |= MC_1 + TASSEL_1 + TACLR ;  // Set Mode -> Up Count, Clock -> ACLK, Clear Timer

    __bis_SR_register(LPM3_bits + GIE); // Go to LPM3 (Only ACLK active), Enable CPU Interrupt

    while(1);

}

#pragma vector = TIMER0_A0_VECTOR       // CCR0 Interrupt Vector
__interrupt void CCR0_ISR(void){
    P1OUT ^= RedLed;                    // Toggle LED
    if(Counter >= 0 && Counter < 2){
        TACCR0 = 10000;                 // Short Delay
        Counter++;
    }
    else if(Counter >= 2){
        TACCR0 = 40000;                 // Long Delay
        Counter++;
        if(Counter == 4){
            Counter = 0;
        }
    }
}*/

