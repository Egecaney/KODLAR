#include <msp430.h> 

/* WDT is clocked by fSMCLK (assumed 1MHz) /
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL)                         / 32ms interval (default) /
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS0)                  / 8ms     " /
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1)                  / 0.5ms   " /
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1+WDTIS0)           / 0.064ms " */

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDT_ADLY_1000;    // stop watchdog timer

    P1DIR |= BIT0+BIT6;
    P1DIR &= ~BIT3;

    P1OUT &= ~(BIT0+BIT6);

    P1OUT &= ~BIT3;
    P1REN |= BIT3;

    P1OUT |= BIT3;

    while(1){
        if(!(P1IN&BIT3)){
            WDTCTL = WDT_ADLY_1000;
            while(!(P1IN&BIT3)){
                if(IFG1&WDTIFG){
                    P1OUT &= ~BIT6;
                    P1OUT ^= BIT0;
                    IFG1 &= ~WDTIFG;
                }
            }
        }
        else{
            WDTCTL = WDT_ADLY_250;
            while((P1IN&BIT3)){
                if(IFG1&WDTIFG){
                    P1OUT &= ~BIT0;
                    P1OUT ^= BIT6;
                    IFG1 &= ~WDTIFG;
                }
            }
        }
    }
}
