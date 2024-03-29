#include <msp430.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

volatile int temp[50];
volatile int diff[50];

volatile unsigned int i=0;
volatile unsigned int j=0;

char th_char[5];
char tl_char[5];
char hh_char[5];
char hl_char[5];

volatile int hh = 0;
volatile int hl = 0;
volatile int th = 0;
volatile int tl = 0;

volatile int check = 0;
volatile int checksum = 0;

volatile int dataok;
char temperature[] = "Temperature is: ";
char dot[] = ".";
char celcius[] = " degrees Celcius  ";
char humidity[] = "Humidity is: ";
char percent[] = " %\r\n";

void ser_output(char *str);
void main(void){

     WDTCTL = WDTPW | WDTHOLD;
     BCSCTL1= CALBC1_1MHZ;
     DCOCTL = CALDCO_1MHZ;

     P1SEL = BIT1|BIT2;
     P1SEL2 = BIT1|BIT2;  // UART Pins

     UCA0CTL1 |= UCSWRST+UCSSEL_2;
     UCA0BR0 = 52;
     UCA0BR1 = 0;
     UCA0MCTL = UCBRS_0;
     UCA0CTL1 &= ~UCSWRST;
     __delay_cycles(2000000);

     P2DIR |= BIT4;       // DHT11 Dijital Pin
     P2OUT &= ~BIT4;
     __delay_cycles(20000);

     P2OUT |= BIT4;
     __delay_cycles(20);
     P2DIR &= ~BIT4;
     P2SEL |= BIT4;

     while(1){

             for(j = 1; j <= 8; j++){
                 if(diff[j] >= 110)
                     hh |= (0x01 << (8-j));
                 }
             for(j = 9; j <= 16; j++){
                 if(diff[j] >= 110)
                     hl |= (0x01 << (16-j));
             }
             for(j = 17; j <= 24; j++){
                 if(diff[j] >= 110)
                     th |= (0x01 << (24-j));
             }
             for(j = 25; j <= 32; j++){
                 if(diff[j] >= 110)
                     tl |= (0x01 << (32-j));
             }
             for(j = 33; j<=40; j++){
                 if(diff[j] >= 110)
                     checksum |= (0x01 << (40-j));
             }
             check=hh+hl+th+tl;
             if(check == checksum)
                 dataok = 1;
             else
                 dataok = 0;

             ltoa(th,th_char,10);
             ltoa(tl,tl_char,10);
             ltoa(hh,hh_char,10);
             ltoa(hl,hl_char,10);
             ser_output(temperature); ser_output(th_char); ser_output(dot); ser_output(tl_char); ser_output(celcius);
             ser_output(humidity); ser_output(hh_char); ser_output(dot); ser_output(hl_char); ser_output(percent);
             __delay_cycles(1000000);

     }
}

void ser_output(char *str){
    while(*str != 0){
        while (!(IFG2&UCA0TXIFG));
        UCA0TXBUF = *str++;
    }
}
