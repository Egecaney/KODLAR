#include <msp430.h> 


/* BUTONA BASIP LED DEÐÝÞTÝRME (Sürekli Basmaya Gerek YOK)
#define Switch     BIT3                        // Switch -> P1.3
#define RedLed     BIT6                        // Red LED -> P1.6
#define GreenLed   BIT0                        // Green LED -> P1.0

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;                  // Stop Watchdog Timer

    P1DIR |= RedLed+GreenLed;                  // Set LED pins -> Output
    P1DIR &= ~Switch;                          // Set SW pin -> Input
    P1REN |= Switch;                           // Enable Resistor for SW pin
    P1OUT |= Switch;                           // Select Pull Up for SW pin

    volatile unsigned int flag = 0;
    while(1){

        if(!(P1IN & Switch)){                  // If SW is Pressed

            __delay_cycles(20000);             // Wait 20ms
            if(!(P1IN & Switch)){              // Check if SW is still pressed
                                               // Ignores presses shorter than 20ms
                while(!(P1IN & Switch));       // Wait till SW Released
                flag = !flag;                  // Change flag value
            }
        }
        if(flag){                              // Check flag value
            P1OUT &= ~GreenLed;                // Green -> OFF
            P1OUT |= RedLed;                   // Red -> ON
        }
        else{
            P1OUT &= ~RedLed;                  // Red -> OFF
            P1OUT |= GreenLed;                 // Green -> ON
        }
    }
}
*/

/* BUTON'A BASIP LED'ÝN DURUMUNU DEÐÝÞTÝRME
#define Switch   BIT3               // Switch -> P1.3
#define GreenLED BIT0               // Green LED -> P1.0

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    P1DIR |= GreenLED;              // Set LED pin -> Output
    P1DIR &= ~Switch;               // Set SW pin -> Input
    P1REN |= Switch;                // Enable Resistor for SW pin
    P1OUT |= Switch;                // Select Pull Up for SW pin

    P1OUT &= Switch;                // P1 is zero without P1.3 because of Pull Up Conf.
    while(1){
        if(!(P1IN&Switch)){             // If SW is Pressed (BUTONA BASTIÐIMDA ÝÇERÝ GÝRECEK)
            __delay_cycles(5000);       // Wait 5ms to debounce (DELAY KOYMA NEDENÝ, ELÝNÝ KALDIRMANA ZAMAN TANIYOR.)
            while(!(P1IN & Switch));    // Wait till SW Released (EÐER BUTONDAN ELÝMÝ KALDIRMAZSAM BURADA DÖNGÜDE KALACAK)
            P1OUT ^= GreenLED;          // Toggle LED (BUTONDAN ELÝMÝ KALDIRIRSAM LED'ÝN DURUMU DEÐÝÞECEK.)
        }
    }
}
*/

//
#define Switch   BIT3                   // Switch  -> P1.3
#define RedLed   BIT6                   // RED LED -> P1.6
volatile int Flag = 1;

void main(void){

    WDTCTL = WDTPW | WDTHOLD;           // Stop Watchdog Timer

    P1OUT = 0x00;
    P1DIR |= RedLed;                    // Set LED pin -> Output
    P1DIR &= ~Switch;                   // Set Switch pin -> Input
    P1REN |= Switch;                    // Enable Resistor for Switch pin
    P1OUT |= Switch;                    // Select Pull Up for Switch pin

    P1IES |= Switch;                    // Select Interrupt on Falling Edge
    P1IE |= Switch;                     // Enable Interrupt on Switch pin

    TA0CCR0 = 50000;                     // Set Timer Timeout Value
    TA0CCTL0 |= CCIE;                    // Enable Overflow Interrupt
    TA0CTL |= MC_1 + TASSEL_1 + TACLR ;  // Set Mode -> Up Count, Clock -> ACLK, Clear Timer

    __bis_SR_register(LPM3_bits + GIE); // Enter LPM4 and Enable CPU Interrupt
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){
    if(Flag){
        TA0CCR0 = 10000;
        Flag = 0;
    }
    else{
        TA0CCR0 = 50000;
        Flag = 1;
    }
    P1IFG &= ~Switch;                   // Clear SW interrupt flag
    P1IES ^= Switch;
}

#pragma vector = TIMER0_A0_VECTOR       // CCR0 Interrupt Vector
__interrupt void CCR0_ISR(void){
    P1OUT ^= RedLed;                    // Toggle LED
}
