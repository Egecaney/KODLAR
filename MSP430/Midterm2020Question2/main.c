#include <msp430.h> 
unsigned int ButtonCounter = 0;

int main(void){

	WDTCTL = WDTPW | WDTHOLD;
	P1SEL = 0x0000;
	P1DIR &= ~BIT3;
	P1DIR |= BIT0+BIT6;
	P1REN |= BIT3;
	P1OUT |= BIT3;

	while(ButtonCounter != 10){
	    while((P1IN&BIT3)){
	    }
	    while(!(P1IN&BIT3)){
	    }
	    ButtonCounter +=1;
	}
	while(ButtonCounter == 10){
	    P1OUT |= BIT0+BIT6;
	}

}
