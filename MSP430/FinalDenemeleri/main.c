#include <msp430.h> 

/*
#define RedLed   BIT6
#define GreenLed BIT0
#define Switch   BIT3

int main(void){
	WDTCTL = WDTPW | WDTHOLD;	// Stop Watchdog Timer

	P1SEL = 0x00;
	P1OUT = 0x00;

	P1DIR |= (GreenLed+RedLed);         // Set LED pins -> Output
    P1DIR &= ~Switch;                   // Set Switch pin -> Input
    P1REN |= Switch;                    // Enable Resistor for Switch pin
    P1OUT |= Switch;                    // Select Pull Up for Switch pin
	
    P1IES |= Switch;                    // Select Interrupt on Falling Edge
    P1IE  |= Switch;                    // Enable Interrupt on Switch pin

    __bis_SR_register(LPM4_bits + GIE); // Enter LPM4 and Enable CPU Interrupt
    while(1);
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){
    volatile int NotAgain = 1;
    volatile int i = 0;
    for(i=0;i<2;i++){
        if((P1IES&Switch) && NotAgain){
           P1OUT ^= RedLed;
           __delay_cycles(500000);
           if(i==1){
              P1IES &= ~Switch;           // Select Interrupt on Rising Edge
              NotAgain = 0;
           }
        }
        if(!(P1IES&Switch) && NotAgain){
           P1OUT ^= GreenLed;
           __delay_cycles(500000);
           if(i==1){
              P1IES |= Switch;            // Select Interrupt on Falling Edge
              NotAgain = 0;
           }
        }
    }
    P1IFG &= ~Switch;                   // Clear SW interrupt flag
}*/


unsigned volatile int counter = 0;

int main(void){
    WDTCTL = WDTPW | WDTHOLD;    // stop watchdog timer

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    TA0CTL = TASSEL_2 | TACLR | ID_0 | MC_1;
    TA0CCR0 = 50000-1;
    TA0CCTL0 |= CCIE;

    for(;;){
        __bis_SR_register(LPM1_bits + GIE);
        P1OUT ^= BIT0;
    }
}

#pragma vector = TIMER0_A0_VECTOR
interrupt void led_blink_timer(void){
    //TA0CCTL0 &= ~CCIFG;
    counter++;
    if(counter == 20){
        counter = 0;
        __bic_SR_register_on_exit(CPUOFF);
    }
}
