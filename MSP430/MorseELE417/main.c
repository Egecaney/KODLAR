#include <msp430.h>

void blink(const int duration);
void delay(const int duration);

void main()
{
    WDTCTL = WDTPW | WDTHOLD;


    P1DIR = BIT0;
    P1OUT &= ~BIT0;
    while(1) {
    while(!(P1IN&BIT3)){
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
    }
}

void blink(const int duration)
{
    if(!(P1IN & BIT3))
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

}

void delay(const int duration)
{
    if(!(P1IN & BIT3))
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

    }

}
