#include <msp430.h> 
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define Enable_RX_Interrupt    IE2 |= UCA0RXIE;
#define Disable_RX_Interrupt   IE2 &= ~UCA0RXIE;

void SetUART(void);
void StartDelay(void);
// void OnlyDelay(int CCR);
void Serial_Output(char *str);
void Wifi_Connect(char *SSID ,char *Password);
void Connect_Broker(char *Ip ,char *Port);
void Subscribe(char *Topic);
void Publish(char *Topic, char *Message);

char TXBuffer[150];
char RXBuffer[80];
unsigned short UartCounter = 0;
bool OKFlag = false;

char *ProtocolName = "MQTT";
char *ClientID = "g25eca";
char *UserName = "g25eca";
char *UserPassword = "e737";

uint16_t ProtocolNameLength;
uint16_t ClientIDLength;
uint16_t UserNameLength;
uint16_t UserPasswordLength;

uint16_t KeepAlive = 60;
uint16_t PacketID = 0x01;
uint8_t  Connect = 0x10;
uint8_t  PublishCon = 0x30;
uint8_t  SubscribeCon = 0x82;
uint8_t  Level = 0x04;
uint8_t  Flag = 0xC2;
uint8_t  Qos = 0x00;

int main(void){

    WDTCTL = WDTPW | WDTHOLD;
    if(CALBC1_1MHZ==0xFF){               // Check if calibration constant erased
        while(1);                        // Do not load program
    }
    DCOCTL = 0;                          // Select lowest DCO settings
    BCSCTL1 = CALBC1_1MHZ;               // Set DCO to 1 MHz
    DCOCTL = CALDCO_1MHZ;

    // Control LED
    P1DIR |= BIT0;
    P1OUT = 0x00;

    /*TIMER For Only Delay
    TA0CTL = TASSEL_1 + ID_3 + TACLR;
    TA0CCR0 = 4095;                      // 1 Second
    TA0CCTL0 |= CCIE;                    // Enable Interrupt for Týmer0 A0
    OnlyDelay(4095);*/

    // TIMER For Transmit Delay
    TA1CTL = TASSEL_1 + ID_0 + TACLR;
    TA1CCR0 = 499;                       // 15 Milisecond
    TA1CCTL0 |= CCIE;                    // Enable Interrupt for Týmer0 A0
    StartDelay();

    // UART Connections
    SetUART();

    // Wifi Connection
    Wifi_Connect("Egemen","69709399ege");

    // Connect Broker
    Connect_Broker("iot.ee.hacettepe.edu.tr","1883");

    // Subscribe("IOT");
    while (1){
        Publish("g25temperature","25");
    }

}

void StartDelay(){
    TA1CTL |= MC_1;                     // Start Timer1 for Small Delay
    __bis_SR_register(LPM3_bits+GIE);   // Sleep During Delay
}

/*
void OnlyDelay(int CCR){
    TA0CTL |= MC_1;                     // Start Timer0 for Small Delay
    TA0CCR0 = CCR;
    __bis_SR_register(LPM3_bits+GIE);   // Sleep During Delay
}*/

void SetUART(void){

    P1SEL  |= BIT1+BIT2;                // RXD - TXD
    P1SEL2 |= BIT1+BIT2;

    UCA0CTL1 |= UCSWRST;                // Initialize UART Module
    UCA0CTL0 |= UCSSEL_0;               // UART Clock
    UCA0CTL1 |= UCSSEL_2|UCSWRST;
    UCA0MCTL |= UCBRF_0|UCBRS_6;
    UCA0BR0 = 8;
    UCA0BR1 = 00;
    UCA0CTL1 &= ~UCSWRST;               // Initialize UART Module

    Disable_RX_Interrupt;
}

void Wifi_Connect(char *SSID ,char *Password){

    while(!OKFlag){
        Serial_Output("AT+RST\r\n");
        Enable_RX_Interrupt;
        StartDelay();
    }
    __delay_cycles(1000000);

    OKFlag = false;
    while(!OKFlag){
        Serial_Output("AT\r\n");
        Enable_RX_Interrupt;
        StartDelay();
    }

    OKFlag = false;
    while(!OKFlag){
        Serial_Output("AT+CWMODE=1\r\n");
        Enable_RX_Interrupt;
        StartDelay();
    }

    /*OKFlag = false;
      while(!OKFlag){
        Serial_Output("AT+CWQAP\r\n");
        Enable_RX_Interrupt;
        StartDelay();
    }*/

    sprintf(TXBuffer,"AT+CWJAP=\"%s\",\"%s\"\r\n",SSID,Password);
    Serial_Output(TXBuffer);
    __delay_cycles(2000000);
}

void Connect_Broker(char *Ip ,char *Port){

    OKFlag = false;
    while(!OKFlag){
        Serial_Output("AT+CIPCLOSE\r\n");
        Enable_RX_Interrupt;
        StartDelay();
    __delay_cycles(2000000);
    }

    OKFlag = false;
    while(!OKFlag){
        Serial_Output("AT+CIPMUX=0\r\n");
        Enable_RX_Interrupt;
        StartDelay();
        __delay_cycles(2000000);

    }

    /*OKFlag = false;
      while(!OKFlag){
        Serial_Output("AT+CIFSR\r\n");
        Enable_RX_Interrupt;
        StartDelay();
        __delay_cycles(2000000);
    }*/

    OKFlag = false;
    sprintf(TXBuffer,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",Ip,Port);
    while(!OKFlag){
        Serial_Output(TXBuffer);
        Enable_RX_Interrupt;
        StartDelay();
    }

    // Connect Packet
    ProtocolNameLength = strlen(ProtocolName);
    ClientIDLength     = strlen(ClientID);
    UserNameLength     = strlen(UserName);
    UserPasswordLength = strlen(UserPassword);
    uint8_t RemainLength;
    RemainLength = 2 + ProtocolNameLength + 6 + ClientIDLength +2 + UserNameLength +2 + UserPasswordLength;

    uint16_t Length = sprintf(TXBuffer,"%c%c%c%c%s%c%c%c%c%c%c%s%c%c%s%c%c%s",(char)Connect,(char)RemainLength,(char)(ProtocolNameLength << 8),(char)ProtocolNameLength,ProtocolName,(char)Level,(char)Flag,(char)(KeepAlive << 8),(char)KeepAlive,(char)(ClientIDLength << 8),(char)ClientIDLength,ClientID,(char)(UserNameLength<<8),(char)UserNameLength,UserName,(char)(UserPasswordLength<<8),(char)UserPasswordLength,UserPassword);
    sprintf(TXBuffer,"AT+CIPSEND=%d\r\n",Length);
    OKFlag = false;
    while(!OKFlag){
        Serial_Output(TXBuffer);
        Enable_RX_Interrupt;
        StartDelay();
    }

    OKFlag = false;
    sprintf(TXBuffer,"%c%c%c%c%s%c%c%c%c%c%c%s%c%c%s%c%c%s",(char)Connect,(char)RemainLength,(char)(ProtocolNameLength << 8),(char)ProtocolNameLength,ProtocolName,(char)Level,(char)Flag,(char)(KeepAlive << 8),(char)KeepAlive,(char)(ClientIDLength << 8),(char)ClientIDLength,ClientID,(char)(UserNameLength<<8),(char)UserNameLength,UserName,(char)(UserPasswordLength<<8),(char)UserPasswordLength,UserPassword);
    while(!OKFlag){
        Serial_Output(TXBuffer);
        Enable_RX_Interrupt;
        StartDelay();
    }

}

void Subscribe(char *Topic){

    uint16_t TopicLength  = strlen(Topic);
    uint8_t  RemainLength = 2+2+TopicLength+1;   // packetIDlength(2) + topiclengthdata(2) + topiclength + Qos
    uint16_t Length = sprintf(TXBuffer,"%c%c%c%c%c%c%s%c",(char)SubscribeCon,(char)RemainLength,(char)(PacketID << 8),(char)PacketID,(char)(TopicLength << 8),(char)TopicLength,Topic,(char)Qos);

    OKFlag = false;
    sprintf(TXBuffer,"AT+CIPSEND=%d\r\n",Length);
    while(!OKFlag){
        Serial_Output(TXBuffer);
        Enable_RX_Interrupt;
        StartDelay();
    }

    OKFlag = false;
    sprintf(TXBuffer,"%c%c%c%c%c%c%s%c",(char)SubscribeCon,(char)RemainLength,(char)(PacketID << 8),(char)PacketID,(char)(TopicLength << 8),(char)TopicLength,Topic,(char)Qos);
    while(!OKFlag){
        Serial_Output(TXBuffer);
        Enable_RX_Interrupt;
        StartDelay();
    }

}

void Publish(char *Topic, char *Message){

    uint16_t TopicLength = strlen(Topic);
    uint8_t  RemainLength = 2+TopicLength+strlen(Message);
    int Length = sprintf(TXBuffer,"%c%c%c%c%s%s",(char)PublishCon,(char)RemainLength,(char)(TopicLength << 8),(char)TopicLength,Topic,Message);

    OKFlag = false;
    sprintf(TXBuffer,"AT+CIPSEND=%d\r\n",Length);
    while(!OKFlag){
        Serial_Output(TXBuffer);
        Enable_RX_Interrupt;
        StartDelay();
    }

    OKFlag = false;
    sprintf(TXBuffer,"%c%c%c%c%s%s",(char)PublishCon,(char)RemainLength,(char)(TopicLength << 8),(char)TopicLength,Topic,Message);
    while(!OKFlag){
        Serial_Output(TXBuffer);
        Enable_RX_Interrupt;
        StartDelay();
    }
}

void Serial_Output(char *String){
    while(*String != 0){
        while (!(IFG2&UCA0TXIFG));
        UCA0TXBUF = *String++;
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void){
    TA0CTL &=~(BIT4+BIT5);
    TA0CTL |= TACLR;
    Disable_RX_Interrupt;
    __bic_SR_register_on_exit(CPUOFF);    // Disable Sleep Mode to Cont. Operation
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void){
    TA1CTL &=~(BIT4+BIT5);
    TA1CTL |= TACLR;
    __bic_SR_register_on_exit(CPUOFF);    // Disable Sleep Mode to Cont. Operation
}

#pragma vector = USCIAB0RX_VECTOR         // UART RX Interrupt Vector
__interrupt void USCI0RX_ISR(void){
    uint8_t i;
    if(UartCounter<80){
        RXBuffer[UartCounter] = UCA0RXBUF;
        if(UartCounter>0){
            if(RXBuffer[UartCounter-1]=='O' && RXBuffer[UartCounter]=='K'){
                Disable_RX_Interrupt;
                UartCounter = 0;
                P1OUT ^= BIT0;
                OKFlag = true;
                for(i=0;i<80;i++){
                    RXBuffer[i] = '\0';
                }
            }
        }
    }
    else{
        UartCounter = 0;
        for(i=0;i<80;i++){
            RXBuffer[i] = '\0';
        }
    }
    UartCounter++;
}
