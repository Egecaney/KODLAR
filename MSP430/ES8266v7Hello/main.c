#include <msp430.h> 
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define Enable_RX_Interrupt    IE2 |= UCA0RXIE;
#define Disable_RX_Interrupt   IE2 &= ~UCA0RXIE;

char TX_Buffer[100];
char RX_Buffer[100];
unsigned short UartRX_Counter = 0;
unsigned volatile int SecondCounter_in_ms = 0;
unsigned short State = 0;

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
void Serial_Output(char *String);
void Delay_in_ms(int Milisecond);
unsigned int Is_Receive_Send_OK(void);
void Clean_RXBuffer(void);
void Clean_TXBuffer(void);

int main(void){

    WDTCTL = WDTPW | WDTHOLD;
    if(CALBC1_1MHZ==0xFF){               // Check if calibration constant erased
        while(1);                        // Do not load program
    }
    DCOCTL = 0;                          // Select lowest DCO settings
    BCSCTL1 = CALBC1_1MHZ;               // Set DCO to 1 MHz
    DCOCTL = CALDCO_1MHZ;

    P1DIR |= BIT0;         // Control LED
    P1OUT = 0x00;

    // UART and Timer SETUP
    SetTimer();
    SetUART();

    // Wifi Connection
    Wifi_Connect("Egemen","69709399ege");

    //Connect IP
    Connect_IP("iot.ee.hacettepe.edu.tr","1883");

    // Connect Broker
    Connect_Broker("g33mas","g33mas","23fa");

    // Subscribe("IOT");
    while (1){
        Publish("g33","Temp=23");
        __delay_cycles(2400000);
        Publish("g33","Temp=23");
        __delay_cycles(2400000);
        Publish("g33","Temp=23");
        Publish("g33","Temp=23");
        __delay_cycles(2400000);
        Publish("g33","Temp=23");
        __delay_cycles(2400000);
        Publish("g33","Temp=23");
        __delay_cycles(2400000);
        Publish("g33","Temp=26");
        __delay_cycles(2400000);
        Publish("g33","Temp=27");
        __delay_cycles(2400000);
        Publish("g33","Temp=29");
        __delay_cycles(2400000);
        Publish("g33","Temp=32");
        __delay_cycles(2400000);
        Publish("g33","Temp=34");
        __delay_cycles(2400000);
        Publish("g33","Temp=35");
        __delay_cycles(2400000);
        Publish("g33","Temp=37");
        __delay_cycles(2400000);
        Publish("g33","Temp=38");
        __delay_cycles(2400000);
        Publish("g33","Temp=38");
        __delay_cycles(2400000);
        Publish("g33","Temp=37");
        __delay_cycles(2400000);
        Publish("g33","Temp=38");
        __delay_cycles(2400000);
        Publish("g33","Temp=37");
        __delay_cycles(2400000);
        Publish("g33","Temp=37");
        __delay_cycles(2400000);
        Publish("g33","Temp=37");
        __delay_cycles(2400000);
        Publish("g33","Temp=38");
        __delay_cycles(2400000);
        Publish("g33","Temp=39");
        __delay_cycles(2400000);
        Publish("g33","Temp=40");
        __delay_cycles(2400000);
        Publish("g33","Temp=40");
        __delay_cycles(2400000);
        Publish("g33","Temp=38");
        __delay_cycles(2400000);
        Publish("g33","Temp=36");
        __delay_cycles(2400000);
        Publish("g33","Temp=35");
        __delay_cycles(2400000);
        Publish("g33","Temp=32");
        __delay_cycles(2400000);
        Publish("g33","Temp=31");
        __delay_cycles(2400000);
        Publish("g33","Temp=30");
        __delay_cycles(2400000);
        Publish("g33","Temp=29");
        __delay_cycles(2400000);
        Publish("g33","Temp=27");
        __delay_cycles(2400000);
        Publish("g33","Temp=26");
        __delay_cycles(2400000);
        Publish("g33","Temp=25");
        __delay_cycles(2400000);
        Publish("g33","Temp=25");
        __delay_cycles(2400000);
        Publish("g33","Temp=25");
        __delay_cycles(2400000);
    }

}

void Wifi_Connect(char *SSID ,char *Password){

    UART_Transmit_String("AT+RST\r\n",(unsigned short)strlen("AT+RST\r\n"));
    Enable_RX_Interrupt;
    Delay_in_ms(15);
    while(!(Is_Receive_Send_OK())){
        UART_Transmit_String("AT+RST\r\n",(unsigned short)strlen("AT+RST\r\n"));
        Enable_RX_Interrupt;
        Delay_in_ms(15);
    }
    Delay_in_ms(1000);

    UART_Transmit_String("AT\r\n",(unsigned short)strlen("AT\r\n"));
    Enable_RX_Interrupt;
    Delay_in_ms(15);
    while(!(Is_Receive_Send_OK())){
        UART_Transmit_String("AT\r\n",(unsigned short)strlen("AT\r\n"));
        Enable_RX_Interrupt;
        Delay_in_ms(15);
    }

    UART_Transmit_String("AT+CWMODE=1\r\n",(unsigned short)strlen("AT+CWMODE=1\r\n"));
    Enable_RX_Interrupt;
    Delay_in_ms(10);
    while(!(Is_Receive_Send_OK())){
        UART_Transmit_String("AT+CWMODE=1\r\n",(unsigned short)strlen("AT+CWMODE=1\r\n"));
        Enable_RX_Interrupt;
        Delay_in_ms(10);
    }

    sprintf(TX_Buffer,"AT+CWJAP=\"%s\",\"%s\"\r\n",SSID,Password);
    UART_Transmit_String(TX_Buffer,strlen(TX_Buffer));
    Clean_TXBuffer();
    Delay_in_ms(2000);
    Clean_RXBuffer();
    /*
    UART_Transmit_String("AT+CWMODE=1\r\n",(unsigned short)strlen("AT+CWMODE=1\r\n"));
    UART_Transmit_String("AT+CWJAP=\"", (unsigned short)strlen("AT+CWJAP=\""));
    UART_Transmit_String(SSID, (unsigned short)strlen(SSID));
    UART_Transmit_String("\",\"", (unsigned short)strlen("\",\""));
    UART_Transmit_String(Password, (unsigned short)strlen(Password));
    UART_Transmit_String("\"\r\n", (unsigned short)strlen("\"\r\n"));
    Delay_in_ms(2000);*/
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

    unsigned short Length = sprintf(TX_Buffer,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",Ip,Port);
    UART_Transmit_String(TX_Buffer,Length);
    Enable_RX_Interrupt;
    Delay_in_ms(2000);
    while(!(Is_Receive_Send_OK())){
        UART_Transmit_String(TX_Buffer,Length);
        Enable_RX_Interrupt;
        Delay_in_ms(2000);
    }
    Clean_TXBuffer();
}

void Connect_Broker(char *ClientID, char *UserName, char *UserPassword){

    uint16_t KeepAlive = 100;
    uint8_t  Connect = 0x10;
    uint8_t  Level = 0x04;
    uint8_t  Flag = 0xC2;
    uint16_t ProtocolNameLength = strlen(ProtocolName);
    uint16_t ClientIDLength = strlen(ClientID);
    uint16_t UserNameLength = strlen(UserName);
    uint16_t UserPasswordLength = strlen(UserPassword);

    uint8_t RemainLength = 2 + ProtocolNameLength + 6 + ClientIDLength + 2 + UserNameLength + 2 + UserPasswordLength;

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

    uint16_t TotalLength = sprintf(TX_Buffer,"%c%c%c%c%s%c%c%c%c%c%c%s%c%c%s%c%c%s",(char)Connect,(char)RemainLength,(char)(ProtocolNameLength << 8),(char)ProtocolNameLength,ProtocolName,(char)Level,(char)Flag,(char)(KeepAlive << 8),(char)KeepAlive,(char)(ClientIDLength << 8),(char)ClientIDLength,ClientID,(char)(UserNameLength<<8),(char)UserNameLength,UserName,(char)(UserPasswordLength<<8),(char)UserPasswordLength,UserPassword);

    Clean_TXBuffer();
    sprintf(TX_Buffer,"AT+CIPSEND=%d\r\n",TotalLength);
    UART_Transmit_String(TX_Buffer, (unsigned short)TotalLength);
    Clean_TXBuffer();
    Delay_in_ms(100);
    Clean_RXBuffer();

    sprintf(TX_Buffer,"%c%c%c%c%s%c%c%c%c%c%c%s%c%c%s%c%c%s",(char)Connect,(char)RemainLength,(char)(ProtocolNameLength << 8),(char)ProtocolNameLength,ProtocolName,(char)Level,(char)Flag,(char)(KeepAlive << 8),(char)KeepAlive,(char)(ClientIDLength << 8),(char)ClientIDLength,ClientID,(char)(UserNameLength<<8),(char)UserNameLength,UserName,(char)(UserPasswordLength<<8),(char)UserPasswordLength,UserPassword);
    UART_Transmit_String(TX_Buffer, (unsigned short)TotalLength);
    Clean_TXBuffer();
    Delay_in_ms(100);
    Clean_RXBuffer();
}

void Publish(char *Topic, char *Message){

    uint8_t MessageLength = strlen(Message);
    uint16_t TopicLength = strlen(Topic);
    uint8_t  RemainLength = 2 + TopicLength + MessageLength;

    /*
      (char)PublishCon          1
      (char)RemainLength        1
      (char)(TopicLength << 8)  1
      (char)TopicLength         1
      Topic                     4
      Message                   5
    */

    unsigned short Length = sprintf(TX_Buffer,"%c%c%c%c%s%s",(char)PublishCon,(char)RemainLength,(char)(TopicLength << 8),(char)TopicLength,Topic,Message);
    UART_Transmit_String(TX_Buffer,sprintf(TX_Buffer,"AT+CIPSEND=%d\r\n",Length));
    Delay_in_ms(250);
    Clean_TXBuffer();
    Clean_RXBuffer();

    sprintf(TX_Buffer,"%c%c%c%c%s%s",(char)PublishCon,(char)RemainLength,(char)(TopicLength << 8),(char)TopicLength,Topic,Message);
    UART_Transmit_String(TX_Buffer,Length);
    Delay_in_ms(250);
    Clean_TXBuffer();

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
    UCA0CTL0 = 0x00;
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

void Serial_Output(char *String){
    Disable_RX_Interrupt;
    while(*String != 0){
        while (!(IFG2&UCA0TXIFG));
        UCA0TXBUF = *String++;
    }
    Enable_RX_Interrupt;
}
void Clean_RXBuffer(void){
    unsigned short Buffer = 0;
    for(Buffer=0;Buffer<100;Buffer++){
        RX_Buffer[Buffer] = 0;
    }
}

void Clean_TXBuffer(void){
    unsigned short Buffer;
    for(Buffer=0;Buffer<100;Buffer++){
        TX_Buffer[Buffer] = 0;
    }
    SecondCounter_in_ms = 0;
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

