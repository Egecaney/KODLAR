#include <msp430.h> 
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define Enable_RX_Interrupt    IE2 |= UCA0RXIE;
#define Disable_RX_Interrupt   IE2 &= ~UCA0RXIE;

char TX_Buffer[150];
char RX_Buffer[100];
unsigned short UartRX_Counter = 0;
unsigned volatile int SecondCounter_in_ms = 0;

uint16_t PacketID = 0x01;
uint8_t  PublishCon = 0x30;
uint8_t  SubscribeCon = 0x82;
uint8_t  Qos = 0x00;
char *ProtocolName = "MQTT";

void Wifi_Connect(char *SSID ,char *Password);
void Connect_IP(char *Ip ,char *Port);
void Connect_Broker(char *ClientID, char *UserName, char *UserPassword);
void Publish(char *Topic, char *Message);
// void Subscribe(char *Topic);

void SetTimer(void);
void SetUART(void);
void UART_Transmit_String(char *String, unsigned short Length);
void UART_Transmit_Char(char Char);
void Delay_in_ms(int Milisecond);
unsigned int Is_Receive_Send_OK(void);
void Clean_RXBuffer(void);


int main(void){

    WDTCTL = WDTPW | WDTHOLD;

    // UART and Timer SETUP
    SetTimer();
	SetUART();

    // Wifi Connection
    Wifi_Connect("Egemen","69709399ege");

    //Connect IP
    Connect_IP("iot.ee.hacettepe.edu.tr","1883");

    // Connect Broker
    Connect_Broker("g25eca","g25eca","e737");

    // Subscribe("IOT");
    while (1){
        __delay_cycles(2000000);
        Publish("g25","25");
    }

}

void Wifi_Connect(char *SSID ,char *Password){

    UART_Transmit_String("AT\r\n",(unsigned short)strlen("AT\r\n"));
    Enable_RX_Interrupt;
    Delay_in_ms(10);
    while(!(Is_Receive_Send_OK())){
        UART_Transmit_String("AT\r\n",(unsigned short)strlen("AT\r\n"));
        Enable_RX_Interrupt;
        Delay_in_ms(10);
    }

    UART_Transmit_String("AT+CWMODE=1\r\n",(unsigned short)strlen("AT+CWMODE=1\r\n"));
    Enable_RX_Interrupt;
    Delay_in_ms(10);
    while(!(Is_Receive_Send_OK())){
        UART_Transmit_String("AT+CWMODE=1\r\n",(unsigned short)strlen("AT+CWMODE=1\r\n"));
        Enable_RX_Interrupt;
        Delay_in_ms(10);
    }

    UART_Transmit_String("AT+CWJAP=\"", (unsigned short)strlen("AT+CWJAP=\""));
    UART_Transmit_String(SSID, (unsigned short)strlen(SSID));
    UART_Transmit_String("\",\"", (unsigned short)strlen("\",\""));
    UART_Transmit_String(Password, (unsigned short)strlen(Password));
    UART_Transmit_String("\"\r\n", (unsigned short)strlen("\"\r\n"));
    Delay_in_ms(2000);
}

void Connect_IP(char *Ip ,char *Port){

    UART_Transmit_String("AT+CIPCLOSE\r\n",(unsigned short)strlen("AT+CIPCLOSE\r\n"));
    Enable_RX_Interrupt;
    Delay_in_ms(1000);
    while(!(Is_Receive_Send_OK())){
        UART_Transmit_String("AT+CIPCLOSE\r\n",(unsigned short)strlen("AT+CIPCLOSE\r\n"));
        Enable_RX_Interrupt;
        Delay_in_ms(1000);
    }

    UART_Transmit_String("AT+CIPMUX=0\r\n",(unsigned short)strlen("AT+CIPMUX=0\r\n"));
    Enable_RX_Interrupt;
    Delay_in_ms(1000);
    while(!(Is_Receive_Send_OK())){
        UART_Transmit_String("AT+CIPMUX=0\r\n",(unsigned short)strlen("AT+CIPMUX=0\r\n"));
        Enable_RX_Interrupt;
        Delay_in_ms(1000);
    }

    UART_Transmit_String("AT+CIPSTART=\"TCP\",\"", (unsigned short)strlen("AT+CIPSTART=\"TCP\",\""));
    UART_Transmit_String(Ip, (unsigned short)strlen(Ip));
    UART_Transmit_String("\",", (unsigned short)strlen("\","));
    UART_Transmit_String(Port, (unsigned short)strlen(Port));
    UART_Transmit_String("\r\n", (unsigned short)strlen("\r\n"));
    Enable_RX_Interrupt;
    Delay_in_ms(2000);
    while(!(Is_Receive_Send_OK())){
        UART_Transmit_String("AT+CIPSTART=\"TCP\",\"", (unsigned short)strlen("AT+CIPSTART=\"TCP\",\""));
        UART_Transmit_String(Ip, (unsigned short)strlen(Ip));
        UART_Transmit_String("\",", (unsigned short)strlen("\","));
        UART_Transmit_String(Port, (unsigned short)strlen(Port));
        UART_Transmit_String("\r\n", (unsigned short)strlen("\r\n"));
        Enable_RX_Interrupt;
        Delay_in_ms(2000);
    }
}

void Connect_Broker(char *ClientID, char *UserName, char *UserPassword){

    uint16_t KeepAlive = 60;
    uint8_t  Connect = 0x10;
    uint8_t  Level = 0x04;
    uint8_t  Flag = 0xC2;
    uint16_t ProtocolNameLength = strlen(ProtocolName);
    uint16_t ClientIDLength = strlen(ClientID);
    uint16_t UserNameLength = strlen(UserName);
    uint16_t UserPasswordLength = strlen(UserPassword);

    uint8_t Remainlength = 2 + ProtocolNameLength + 6 + ClientIDLength + 2 + UserNameLength + 2 + UserPasswordLength;

    /*(char)Connect                             1
      (char)RemainLength                        1
      (char)(ProtocolNameLength << 8)           1
      (char)ProtocolNameLength                  1
      ProtocolName                              4
      (char)Level                               1
      (char)Flag                                1
      (char)(KeepAlive << 8)                    1
      (char)KeepAlive                           1
      (char)(ClientIDLength << 8)               1
      (char)ClientIDLength                      1
      ClientID                                  5
      (char)(UserNameLength<<8)                 1
      (char)UserNameLength                      1
      UserName                                  5
      (char)(UserPasswordLength<<8)             1
      (char)UserPasswordLength                  1
      UserPassword                              4
      */
    uint8_t TotalLength = 34 ; //34Byte

    UART_Transmit_String("AT+CIPSEND=", (unsigned short)strlen("AT+CIPSEND="));
    UART_Transmit_Char(TotalLength +'0');
    UART_Transmit_String("\r\n", (unsigned short)strlen("\r\n"));
    Delay_in_ms(100);
    Clean_RXBuffer();

    UART_Transmit_Char((char)Connect);
    UART_Transmit_Char((char)Remainlength);
    UART_Transmit_Char((char)(ProtocolNameLength << 8));
    UART_Transmit_Char((char)ProtocolNameLength);
    UART_Transmit_String(ProtocolName,(unsigned short)strlen(ProtocolName));
    UART_Transmit_Char((char)Level);
    UART_Transmit_Char((char)Flag);
    UART_Transmit_Char((char)(KeepAlive << 8));
    UART_Transmit_Char((char)KeepAlive);
    UART_Transmit_Char((char)(ClientIDLength << 8));
    UART_Transmit_Char((char)ClientIDLength);
    UART_Transmit_String(ClientID,(unsigned short)strlen(ClientID));
    UART_Transmit_Char((char)(UserNameLength << 8));
    UART_Transmit_Char((char)UserNameLength);
    UART_Transmit_String(UserName,(unsigned short)strlen(UserName));
    UART_Transmit_Char((char)(UserPasswordLength << 8));
    UART_Transmit_Char((char)UserPasswordLength);
    UART_Transmit_String(UserPassword,(unsigned short)strlen(UserPassword));
    Delay_in_ms(100);
    Clean_RXBuffer();
}

void Publish(char *Topic, char *Message){

    uint16_t TopicLength = strlen(Topic);
    uint8_t  RemainLength = 2 + TopicLength + strlen(Message);

    /*
      (char)PublishCon          1
      (char)RemainLength        1
      (char)(TopicLength << 8)  1
      (char)TopicLength         1
      Topic                     4
      Message                   5
    */

    uint8_t TotalLength = 4 + 2 + strlen(Message) ;  //19 byte

    UART_Transmit_String("AT+CIPSEND=", (unsigned short)strlen("AT+CIPSEND="));
    UART_Transmit_Char((char)TotalLength);
    UART_Transmit_String("\r\n", (unsigned short)strlen("\r\n"));
    Delay_in_ms(200);

    UART_Transmit_Char((char)PublishCon);
    UART_Transmit_Char((char)RemainLength);
    UART_Transmit_Char((char)(TopicLength << 8));
    UART_Transmit_Char((char)TopicLength);
    UART_Transmit_String(Topic,(unsigned short)strlen(Topic));
    UART_Transmit_String(Message,(unsigned short)strlen(Message));
    Delay_in_ms(200);

}

void SetTimer(void){                      // Use Timer0 A0 for LPM delays
    TA0CTL = TASSEL_2 + TACLR + ID_0 ;    // Clock->SMCLK,
    TA0CCR0 = 1000-1;                     // 1ms Timing
    TA0CCTL0 |= CCIE;                     // Enable Capture/Compare Interrupt for Timer1 A0
}

void SetUART(void){
    P1SEL= BIT1 + BIT2;     // P1.1=RXD P1.2=TXD
    P1SEL2= BIT1 + BIT2;

    UCA0CTL1 |= UCSWRST;
    UCA0CTL0 = UCSSEL_0;
    UCA0CTL1 |= UCSSEL_2 | UCSWRST ;
    UCA0MCTL = UCBRF_0 | UCBRS_6;
    UCA0BR0  = 8;
    UCA0BR1  = 00;
    UCA0CTL1 &= ~UCSWRST;

    Disable_RX_Interrupt;

}

void UART_Transmit_String(char *String, unsigned short Length){
    Disable_RX_Interrupt;
    unsigned short UartTX_Counter = 0;
    while(UartTX_Counter < Length){
        UART_Transmit_Char(*String++);
        UartTX_Counter++;
    }
    Enable_RX_Interrupt;
}

void UART_Transmit_Char(char Char){
    while(!(IFG2&UCA0TXIFG));       // USCI_A0 TX Buffer Ready?
    UCA0TXBUF = Char;               // Char -> TX
}

void Clean_RXBuffer(void){
    unsigned short Buffer = 0;
    for(Buffer=0;Buffer<100;Buffer++){
        RX_Buffer[Buffer] = '\0';
    }
}

void Delay_in_ms(int Milisecond){
    SecondCounter_in_ms = Milisecond;
    TA0CTL |= MC_1;                     // Start Timer for Small Delay
    __bis_SR_register(LPM1_bits + GIE); // Sleep During Delay
}

unsigned int Is_Receive_Send_OK(void){
    unsigned short Buffer_Counter = 0;
    unsigned int OKFlag = 0 ;
    while(1){
        if(RX_Buffer[Buffer_Counter]=='O' && RX_Buffer[Buffer_Counter+1]=='K'){ //OK arayan fonksiyon.
            OKFlag = 1 ;
            break;
        }
        Buffer_Counter++;
        if(Buffer_Counter == 99){
            UartRX_Counter=0;
            break;
        }
    }
    Clean_RXBuffer();
    return OKFlag;
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void Delay(void){
    SecondCounter_in_ms--;
    if(SecondCounter_in_ms == 0){
        TA0CTL &= ~(BIT4 + BIT5);           // Delay is Complete, Disable Counting Mode
        TA0CTL |= TACLR;                    // Clear Timer for the Next Usage
        __bic_SR_register_on_exit(CPUOFF);  // Disable Sleep Mode to Cont. Operation
    }
}

#pragma vector = USCIAB0RX_VECTOR         // UART RX Interrupt Vector
__interrupt void USCI0RX_ISR(void){
    if(UartRX_Counter<100){
        RX_Buffer[UartRX_Counter] = UCA0RXBUF;
        if(UartRX_Counter>0){
            if(RX_Buffer[UartRX_Counter-1]=='O' && RX_Buffer[UartRX_Counter]=='K'){   // If the RX send OK
                Disable_RX_Interrupt;
                UartRX_Counter = 0;
                P1OUT ^= BIT0;         // Control LED
            }
        }
    }
    UartRX_Counter++;
}

/*
void Subscribe(char *Topic){

    uint16_t TopicLength  = strlen(Topic);
    uint8_t  RemainLength = 2+2+TopicLength+1;   // packetIDlength(2) + topiclengthdata(2) + topiclength + Qos
    uint16_t Length = sprintf(TXBuffer,"%c%c%c%c%c%c%s%c",(char)SubscribeCon,(char)RemainLength,(char)(PacketID << 8),(char)PacketID,(char)(TopicLength << 8),(char)TopicLength,Topic,(char)Qos);

    sprintf(TXBuffer,"AT+CIPSEND=%d\r\n",Length);
    Serial_Output(TXBuffer);
    __delay_cycles(100000);

    sprintf(TXBuffer,"%c%c%c%c%c%c%s%c",(char)SubscribeCon,(char)RemainLength,(char)(PacketID << 8),(char)PacketID,(char)(TopicLength << 8),(char)TopicLength,Topic,(char)Qos);
    Serial_Output(TXBuffer);
    __delay_cycles(100000);
}*/
