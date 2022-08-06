#include <msp430.h> 
/*
#define GreenLed BIT0
#define RedLed BIT6
#define Switch BIT3
*/
/*
int main(void){
    WDTCTL = WDTPW|WDTCNTCL|WDTSSEL|WDTTMSEL;//|0x01 ;   // Active Watchdog Timer.
    P1SEL = 0x0000;
    P1DIR |= GreenLed;
    P1OUT &= 0x0000;

    while(1){
        if(IFG1 & WDTIFG){
            P1OUT ^= GreenLed;
            WDTCTL = WDTPW|WDTCNTCL|WDTSSEL|WDTTMSEL;//|0x01 ; // Active again IFG1 = ~WDTIFG (Reset the intterupt flag).
            IFG1 = ~WDTIFG;
        }
    }
}
*/

/* 1.Soru
int main(void){

    WDTCTL = WDT_ADLY_1000;       // WDT_ADLY_1000 = WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL (1000ms)
    P1SEL = 0x0000;
    P1DIR |= GreenLed+RedLed;

    //P1OUT &= ~(GreenLed+RedLed);
    //P1REN |= (GreenLed+RedLed);
    volatile unsigned int Counter =0;


    while(1){
        if(IFG1&WDTIFG){
           IFG1 &= ~WDTIFG;
           Counter++ ;
           if(Counter == 2){
              P1OUT ^= GreenLed;
              Counter = 0;
              if(P1OUT&GreenLed){
                 P1OUT &= ~RedLed;
              }
              else{
                 P1OUT |= RedLed;
              }
           }
        }
    }
}*/

/*
int main(void){

    WDTCTL = WDTPW|WDTHOLD;

    P1SEL = 0x0000;
    P1DIR |= GreenLed+RedLed;
    P1DIR &= ~Switch;

    P1REN |= BIT3;
    P1OUT |= BIT3;

    TA1CTL |= TASSEL1|MC_1|TACLR|ID_0;
    TA1CCR0 = 7999;

    //(1/32000)(8000)(1) = 0.25 sn;

    P1OUT = 0x0000;

    volatile unsigned int count = 0;

    while(1){
        while(!(P1IN&Switch)){

            ShortBlink();

            LongDuration();

            ShortBlink();
            ShortDuration();
            LongBlink();
            ShortDuration();
            ShortBlink();
            ShortDuration();
            ShortBlink();

            LongDuration();

            ShortBlink();

            LongDuration();

            ShortBlink();
            ShortDuration();
            ShortBlink();
            ShortDuration();
            ShortBlink();
            ShortDuration();
            ShortBlink();
            ShortDuration();
            LongBlink();

            LongDuration();

            ShortBlink();
            ShortDuration();
            LongBlink();
            ShortDuration();
            LongBlink();
            ShortDuration();
            LongBlink();
            ShortDuration();
            LongBlink();

            LongDuration();

            LongBlink();
            ShortDuration();
            LongBlink();
            ShortDuration();
            ShortBlink();
            ShortDuration();
            ShortBlink();
            ShortDuration();
            ShortBlink();

        }
    }

}

void ShortBlink(void){

    P1OUT |= GreenLed;
    TA1CCR0 = 64000;
    TA1CTL &= ~TAIFG;
    while((TA1CTL&TAIFG)!= TAIFG);
    P1OUT &= ~GreenLed;
}

void LongBlink(void){

    P1OUT |= GreenLed;
    volatile unsigned int i=0;
    for(i=0;i<2;i++){
        TA1CCR0 = 64000;
        TA1CTL &= ~TAIFG;
        while((TA1CTL&TAIFG)!= TAIFG);
    }
    P1OUT &= ~GreenLed;
}

void LongDuration(void){

    P1OUT = 0x0000;
    volatile unsigned int i=0;
    for(i=0;i<4;i++){
        TA1CCR0 = 7999;
        TA1CTL &= ~TAIFG;
        while((TA1CTL&TAIFG)!= TAIFG);
    }

}

void ShortDuration(void){

    P1OUT = 0x0000;
    volatile unsigned int i=0;
    for(i=0;i<2;i++){
        TA1CCR0 = 7999;
        TA1CTL &= ~TAIFG;
        while((TA1CTL&TAIFG)!= TAIFG);
    }
}
*/

/* Batu
void blink(const int duration);
void delay(const int duration);

void main()
{
    WDTCTL = WDTPW | WDTHOLD;

    //PM5CTL0 &= ~LOCKLPM5; hocanýn kartýnda çalýþtýrmak için gerekli

    P1DIR = BIT0;
    P1OUT &= ~BIT0;

    //E
    blink(0);
    delay(1);
    //L
    blink(0); delay(5); blink(1); delay(5); blink(0); delay(5); blink(0);
    delay(1);
    //E
    blink(0);
    delay(1);
    //4
    blink(0);delay(5);blink(0);delay(5);blink(0);delay(5);blink(0);delay(5);blink(1);
    delay(1);
    //1
    blink(0);delay(5);blink(1);delay(5);blink(1);delay(5);blink(1);delay(5);blink(1);
    delay(1);
    //7
    blink(1);delay(5);blink(1);delay(5);blink(0);delay(5);blink(0);delay(5);blink(0);


}

void blink(const int duration)
{
    TA1CTL &= ~TAIFG;

    if (duration == 0)
    {
        TA1CTL = TASSEL_1 | MC_2 | TACLR | ID_0;
    }
    else if (duration == 1)
    {
        TA1CTL = TASSEL_1 | MC_2 | TACLR | ID_2;
    }

    P1OUT |= BIT0;

    while ((TA1CTL & TAIFG) != TAIFG)
    {
    }
    TA1CTL &= ~TAIFG;
    P1OUT &=  ~BIT0;
}

void delay(const int duration)
{
    P1OUT &=  ~BIT0;
    TA1CTL &= ~TAIFG;

    if (duration == 1)
    {
        TA1CTL = TASSEL_1 | MC_2 | TACLR | ID_1;
    }
    else if (duration == 5)
    {
        TA1CTL = TASSEL_1 | MC_2 | TACLR | ID_0;
    }

    while ((TA1CTL & TAIFG) != TAIFG)
    {
    }
    TA1CTL &= ~TAIFG;
}*/

/* Q.6
#define GreenLed BIT0
#define RedLed BIT6

void main(void){

    WDTCTL = WDT_ADLY_1000;             // WDT is set for 1 second intervals
    P1DIR |= (GreenLed|RedLed);         // P1.0 and P1.6 are configured as outputs

    P1OUT &= ~(GreenLed|RedLed);              // All Leds OFF.
    while(1){
        while(!(IFG1 & WDTIFG));        // Wait for WDT to reach the limit

        // Reaches the limit.
        IFG1 &= ~WDTIFG;                // Clear WDT interrupt flag when counter
        P1OUT ^= (GreenLed|RedLed);           // toggle the LEDs.
    }
}*/

/* Q.7
#define GreenLed BIT0
#define RedLed BIT6

void main(void){

    WDTCTL = WDTPW | WDTHOLD;     // Stop Watchdog Timer

    // Timer A is configured to work in up mode and generate 1 second intervals
    // TASSEL_1 selects ACLK (32 KHz), MC_1 selects up mode
    // TACLR is Timer A counter clear and ID_0 is Timer A input divider with 1
    TA1CTL = TASSEL_1 | MC_1 | TACLR | ID_0;
    TA1CCR0 = 31999;                // Count to 31999

    P1DIR = (GreenLed|RedLed);      //LEDs are configured as outputs
    P1OUT &= ~(GreenLed|RedLed);
    while(1){
        while((TA1CTL & TAIFG) != TAIFG);

        TA1CTL &= ~TAIFG;           // Clear Timer A Interrupt Flag
        P1OUT ^= (GreenLed|RedLed); // Toggle the LEDs
    }
}*/

// Q.8
#define GreenLed BIT0

void TimerA_Delay(int DelayFlag){
    if(DelayFlag){ // Short Delay
        TA1CTL = TA1CTL = TASSEL_1 | MC_1 | TACLR | ID_0;
        TA1CCR0 = 31999;
    }
    else{       // Long Delay
        TA1CTL = TA1CTL = TASSEL_1 | MC_1 | TACLR | ID_1;
        TA1CCR0 = 63999;
    }
    while(!(TA1CTL & TAIFG));
}

void main(void){
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer
    P1DIR = GreenLed;           // P1.0 (Green LED) configured as output
    P1OUT &= ~GreenLed;
    volatile int DelayFlag = 1; // flag controls when to change delay
    while(1){
        if(DelayFlag){
            P1OUT ^= GreenLed;
            TimerA_Delay(DelayFlag);
            P1OUT ^= GreenLed;
            TimerA_Delay(DelayFlag);
            DelayFlag = 0;
        }
        else{
            P1OUT ^= GreenLed;
            TimerA_Delay(DelayFlag);
            P1OUT ^= GreenLed;
            TimerA_Delay(DelayFlag);
            DelayFlag = 1;
        }
    }
}



