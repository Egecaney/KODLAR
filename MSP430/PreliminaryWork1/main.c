#include <msp430.h> 
#include <stdio.h>


/* Pre 1.2
int main(void){
    unsigned int MyNumber = 0x00;  // MyNumber = 00000000
    MyNumber ^= 0x69;              // MyNumber = 00000000 XOR 01101001 = 01101001
    MyNumber ^= 0xFF;              // MyNumber = 01101001 XOR 11111111 = 10010110
    return(0);
}*/

/* Pre 1.6
int main(void){

    WDTCTL = WDTPW | WDTHOLD;          // Stop Watchdog Timer
    volatile unsigned int Aydugan;
    volatile unsigned int Egemen_Can;
    volatile unsigned int i=0;

    Aydugan = 0;
    Egemen_Can = 19;                   // ÇORUM  (0001 0011)

    for(i=0; i<4;i++){                 // Final Egemen_Can = 0001 0011 0000 = 304
        Egemen_Can = Egemen_Can << 1;
    }

    Aydugan = Egemen_Can & 0x30;       // 0001 0011 0000 And 0000 0011 0000 = 0011 0000 = 0x30

    return 0 ;
}*/

// PRE 1.7
int main(void){

    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    P1SEL = 0x0000;             // P1 became GPIO.
    P1DIR |= 0x0001;            // P1.0 pin is output.
    P1OUT= 0x0000;              // Starts with P1.0 = 0.

    volatile unsigned int i=0;
    while(1){

        if(i<2){
            P1OUT = P1OUT ^ 0001;
            __delay_cycles(1000000);    // Delay 1 second (Short Delay)
            i++;
        }
        if(i>=2){
            P1OUT = P1OUT ^ 0001;
            __delay_cycles(3000000);    // Delay 3 second (Long Delay)
            i++;
            if(i==4){
                i=0;
            }
        }
    }
}//

/* Exp 1.1
#define Switch   BIT3               // Switch -> P1.3
#define GreenLED BIT0               // Green LED -> P1.0

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    P1DIR |= GreenLED;              // Set LED pin -> Output
    P1DIR &= ~Switch;               // Set SW pin -> Input
    P1REN |= Switch;                // Enable Resistor for SW pin
    P1OUT |= Switch;                // Select Pull Up for SW pin

    while(1){
        if(!(P1IN&Switch)){             // If SW is Pressed (BUTONA BASTIÐIMDA ÝÇERÝ GÝRECEK)
            while(!(P1IN & Switch));    // Wait till SW Released (EÐER BUTONDAN ELÝMÝ KALDIRMAZSAM BURADA DÖNGÜDE KALACAK)
            P1OUT ^= GreenLED;          // Toggle LED (BUTONDAN ELÝMÝ KALDIRIRSAM LED'ÝN DURUMU DEÐÝÞECEK.)
        }
    }
}//

/* Exp 1.2
#define Switch   BIT3               // Switch -> P1.3
#define GreenLED BIT0               // Green LED -> P1.0

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    P1DIR |= GreenLED;              // Set LED pin -> Output
    P1DIR &= ~Switch;               // Set SW pin -> Input
    P1REN |= Switch;                // Enable Resistor for SW pin
    P1OUT |= Switch;                // Select Pull Up for SW pin

    while(1){
        if(!(P1IN&Switch)){             // If SW is Pressed (BUTONA BASTIÐIMDA ÝÇERÝ GÝRECEK)
            P1OUT ^= GreenLED;          // Toggle LED (BUTONDAN ELÝMÝ KALDIRIRSAM LED'ÝN DURUMU DEÐÝÞECEK.)
            __delay_cycles(100000);
        }
        else{
            P1OUT ^= GreenLED;          // Toggle LED (BUTONDAN ELÝMÝ KALDIRIRSAM LED'ÝN DURUMU DEÐÝÞECEK.)
            __delay_cycles(500000);
        }
    }
}*/


