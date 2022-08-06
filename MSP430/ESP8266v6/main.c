#include <msp430g2553.h>
#include <msp430.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

unsigned short UART_Rx_Counter = 0;
char UART_Rx_Buffer[80];
unsigned volatile int counter = 0;
char tx_buffer[100];
unsigned short mode = 0;

const uint8_t publishCon = 0x30,subscribeCon = 0x82;
char *protocolName = "MQTT";
const uint16_t packetID = 0x01;
const uint8_t Qos = 0x00;

uint8_t averageTemp=0;
uint8_t estimatedTemp=0;

int hum, temp, hour, min, sec;
short buffer_cnt = 0;

void Init_Timer(void);
void Init_UART(void);
void Transmit_UART_Buffer(char *str,unsigned short length);
void Transmit_UART_Char(char c);
unsigned int If_esp8266_ok(void);
void cleanRXBuffer(void);
void cleanTXBuffer(void);
void ConnectNetwork(char *Ip ,char *Port);
void Connect_IP(char *Ip ,char *Port);
void Connect_Broker(char *clientID, char *ID, char *Password);
void DelayGen(int milisecond);
void publish(char *topic);
void subs(char *topic);
void Subscribe(char *topic);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;// Stop Watchdog

    Init_Timer();
    Init_UART();

    ConnectNetwork("fury", "ddew9911");
    Connect_IP("iot.ee.hacettepe.edu.tr","1883");
    Connect_Broker("g32ok","g32ok","f24d");
    Subscribe("g32data");
    __delay_cycles(1000000);
    cleanRXBuffer();
    IE2 |= UCA0RXIE;
    mode = 0;

    while(1){
        if(mode == 1){
            while(UART_Rx_Buffer[buffer_cnt] != '!')
            {
                buffer_cnt++;
                if(buffer_cnt > 79){
                    buffer_cnt = 0;
                    break;
                }
                //__bis_SR_register(LPM1_bits+GIE);
            }
            while(UART_Rx_Buffer[buffer_cnt] != 'g')
            {
                buffer_cnt--;
                if(buffer_cnt < 0){
                    buffer_cnt = 0;
                    break;
                }
            }
            if(UART_Rx_Buffer[buffer_cnt] == 'g'){
                sscanf(&UART_Rx_Buffer[buffer_cnt],"g32data%d,%d,%d,%d,%d",&hum,&temp,&hour,&min,&sec);
                buffer_cnt = 0;
                mode = 0;
                cleanRXBuffer();
                IE2 |= UCA0RXIE;
            }
        }
        //break;
        //__no_operation();
        __delay_cycles(2000000);
    }
}

void Init_UART(void){
    P1SEL= BIT1 + BIT2; //P1.1 = RXD P1.2=TXD
    P1SEL2= BIT1 + BIT2; // P1.1=RXD & P1.2=TXD
    UCA0CTL1 |= UCSWRST;
    UCA0CTL0 = 0x00;
    UCA0CTL1 |= UCSSEL_2 | UCSWRST ;
    UCA0MCTL = UCBRF_0 | UCBRS_6;
    UCA0BR0 = 8;
    UCA0BR1 = 00;
    UCA0CTL1 &= ~UCSWRST;
    IE2 &= ~UCA0RXIE; // DISABLE VSCI_A0 RX INTERRUPT
}

void Transmit_UART_Buffer(char *str,unsigned short length){
    IE2 &= ~UCA0RXIE;//DISABLE RX Interrupt
    unsigned short counter = 0;
    while(counter < length){
        Transmit_UART_Char(*str++);
        counter++;
    }
    IE2 |= UCA0RXIE;  //IE2 |= UCA0RXIE;
}

void Transmit_UART_Char(char c){
    while(!(IFG2&UCA0TXIFG));  // USCI_A0 TX buffer ready ?
    UCA0TXBUF=c; // TX
}

unsigned int If_esp8266_ok(void){
    unsigned short buffer_cont = 0;
    unsigned int ret = 0;
    while(1){
        if(UART_Rx_Buffer[buffer_cont]=='O' && UART_Rx_Buffer[buffer_cont+1]=='K')//OK arayan fonksiyon.
        {
            ret=1;
            break;
        }

        buffer_cont++;

        if(buffer_cont==79)
        {
            UART_Rx_Counter=0;break;
        }

    }
    cleanRXBuffer();
    return ret;
}

void cleanRXBuffer(void){
    unsigned short i;
    for(i=0;i<80;i++){
        UART_Rx_Buffer[i] = 0;
    }
    UART_Rx_Counter = 0;
}

void Connect_Broker(char *clientID, char *ID, char *Password){
    uint8_t connect = 0x10;
    uint8_t level = 0x04;
    uint8_t flag = 0xc2;   //--> sifreli
    uint16_t keepAlive = 100;
    uint16_t ProtocolNameLength = strlen(protocolName);
    uint16_t ClientIDLength = strlen(clientID);
    uint16_t IDLength = strlen(ID);
    uint16_t PasswordLength = strlen(Password);
    uint8_t Remainlength;
    Remainlength = 2 + ProtocolNameLength + 6 + ClientIDLength + 2 + IDLength + 2 + PasswordLength;
    uint16_t length = sprintf(tx_buffer,"%c%c%c%c%s%c%c%c%c%c%c%s%c%c%s%c%c%s",(char)connect,(char)Remainlength,(char)(ProtocolNameLength << 8),(char)ProtocolNameLength,protocolName,(char)level,(char)flag,(char)(keepAlive << 8),(char)keepAlive,
                              (char)(ClientIDLength << 8),(char)ClientIDLength,clientID,
                              (char)(IDLength << 8),(char)IDLength,ID,
                              (char)(PasswordLength << 8),(char)PasswordLength,Password);

    cleanTXBuffer();
    sprintf(tx_buffer,"AT+CIPSEND=%d\r\n",length);
    Transmit_UART_Buffer(tx_buffer, (unsigned short)length);
    cleanTXBuffer();
    DelayGen(100);
    cleanRXBuffer();

    sprintf(tx_buffer,"%c%c%c%c%s%c%c%c%c%c%c%s%c%c%s%c%c%s",(char)connect,(char)Remainlength,(char)(ProtocolNameLength << 8),(char)ProtocolNameLength,protocolName,(char)level,(char)flag,(char)(keepAlive << 8),(char)keepAlive,
            (char)(ClientIDLength << 8),(char)ClientIDLength,clientID,
            (char)(IDLength << 8),(char)IDLength,ID,
            (char)(PasswordLength << 8),(char)PasswordLength,Password);
    Transmit_UART_Buffer(tx_buffer,(unsigned short)length);
    cleanTXBuffer();
    DelayGen(100);
    cleanRXBuffer();
}

void publish(char *topic)
{

    uint8_t messagelength = sprintf(tx_buffer,"AverageTemp=%d, EstTemp=%d",averageTemp,estimatedTemp);
    cleanTXBuffer();

    uint16_t topiclength = strlen(topic);
    uint8_t remainlength = 2 + topiclength + messagelength;

    unsigned short length = sprintf(tx_buffer,"%c%c%c%c%s AverageTemp=%d, EstTemp=%d",(char)publishCon,(char)remainlength,(char)(topiclength << 8),(char)topiclength,topic,averageTemp,estimatedTemp);
    cleanTXBuffer();
    sprintf(tx_buffer,"AT+CIPSEND=%d\r\n",length);
    Transmit_UART_Buffer(tx_buffer,sprintf(tx_buffer,"AT+CIPSEND=%d\r\n",length));
    DelayGen(250);
    cleanTXBuffer();
    cleanRXBuffer();

    sprintf(tx_buffer,"%c%c%c%c%s AverageTemp=%d, EstTemp=%d",(char)publishCon,(char)remainlength,(char)(topiclength << 8),(char)topiclength,topic,averageTemp,estimatedTemp);
    Transmit_UART_Buffer(tx_buffer,length);
    DelayGen(250);
    cleanTXBuffer();
}

void subs(char *topic)
{
    uint16_t topiclength = strlen(topic);
    const uint16_t PackageID = 0x0008;
    uint8_t remainlength = 2 + 2 + topiclength + 1;

    unsigned short length = sprintf(tx_buffer,"%c%c%c%c%c%c%s%c",(char)subscribeCon,(char)remainlength,(char)(PackageID << 8),(char)PackageID,(char)(topiclength << 8),(char)topiclength,topic,Qos);
    cleanTXBuffer();

    cleanRXBuffer();
    sprintf(tx_buffer,"AT+CIPSEND=%d\r\n",length);
    Transmit_UART_Buffer(tx_buffer,length);
    DelayGen(250);
    cleanTXBuffer();

    sprintf(tx_buffer,"%c%c%c%c%c%c%s%c",(char)subscribeCon,(char)remainlength,(char)(PackageID << 8),(char)PackageID,(char)(topiclength << 8),(char)topiclength,topic,Qos);
    Transmit_UART_Buffer(tx_buffer,length);
    DelayGen(250);
    cleanTXBuffer();
}

void Subscribe(char *topic)
{
    uint16_t TopicLength = strlen(topic);
    uint8_t RemainLength = 2+2+TopicLength+1; // packetIDlength(2) + topiclengthdata(2) + topiclength + Qos
    uint16_t length = sprintf(tx_buffer,"%c%c%c%c%c%c%s%c",(char)subscribeCon,(char)RemainLength,(char)(packetID << 8),(char)packetID,(char)(TopicLength << 8),(char)TopicLength,topic,(char)Qos);
    cleanTXBuffer();
    cleanRXBuffer();
    sprintf(tx_buffer,"AT+CIPSEND=%d\r\n",length);
    Transmit_UART_Buffer(tx_buffer,sprintf(tx_buffer,"AT+CIPSEND=%d\r\n",length));
    DelayGen(250);
    cleanTXBuffer();
    sprintf(tx_buffer,"%c%c%c%c%c%c%s%c",(char)subscribeCon,(char)RemainLength,(char)(packetID << 8),(char)packetID,(char)(TopicLength << 8),(char)TopicLength,topic,(char)Qos);
    Transmit_UART_Buffer(tx_buffer,length);
    DelayGen(250);
    cleanTXBuffer();
    cleanRXBuffer();
    // HAL_UART_Transmit(&huart1,(uint8_t *)tx_buffer,sprintf(tx_buffer,"AT+CIPSEND=%d\r\n",length),1000);
    // HAL_UART_Transmit(&huart1,(uint8_t *)tx_buffer,sprintf(tx_buffer,"%c%c%c%c%c%c%s%c",(char)subscribeCon,(char)RemainLength,(char)(packetID << 8),(char)packetID,(char)(TopicLength << 8),(char)TopicLength,topic,(char)Qos),5000);
}


void cleanTXBuffer(void){
    unsigned short i;
    for(i=0;i<100;i++){
        tx_buffer[i] = 0;
    }
    counter = 0;
}

void ConnectNetwork(char *network_id ,char *network_password){
    Transmit_UART_Buffer("AT+RST\r\n",(unsigned short)strlen("AT+RST\r\n"));
    IE2 |= UCA0RXIE;
    DelayGen(10);
    while(!(If_esp8266_ok())){
        Transmit_UART_Buffer("AT+RST\r\n",(unsigned short)strlen("AT+RST\r\n"));
        IE2 |= UCA0RXIE;
        DelayGen(10);
    }
    DelayGen(1000);

    Transmit_UART_Buffer("AT\r\n",(unsigned short)strlen("AT\r\n"));
    IE2 |= UCA0RXIE;
    DelayGen(10);
    while(!(If_esp8266_ok())){
        Transmit_UART_Buffer("AT\r\n",(unsigned short)strlen("AT\r\n"));
        IE2 |= UCA0RXIE;
        DelayGen(10);
    }

    Transmit_UART_Buffer("AT+CWMODE=1\r\n",(unsigned short)strlen("AT+CWMODE=1\r\n"));
    IE2 |= UCA0RXIE;
    DelayGen(10);
    while(!(If_esp8266_ok())){
        Transmit_UART_Buffer("AT+CWMODE=1\r\n",(unsigned short)strlen("AT+CWMODE=1\r\n"));
        IE2 |= UCA0RXIE;
        DelayGen(10);
    }

    Transmit_UART_Buffer("AT+CWJAP=\"",(unsigned short)strlen("AT+CWJAP=\""));
    Transmit_UART_Buffer(network_id,(unsigned short)strlen(network_id));
    Transmit_UART_Buffer("\",\"",(unsigned short)strlen("\",\""));
    Transmit_UART_Buffer(network_password,(unsigned short)strlen(network_password));
    Transmit_UART_Buffer("\"\r\n",(unsigned short)strlen("\"\r\n"));
    DelayGen(2000);
}

void Connect_IP(char *Ip ,char *Port){
    //if connected any server, disconnect
    Transmit_UART_Buffer("AT+CIPCLOSE\r\n",(unsigned short)strlen("AT+CIPCLOSE\r\n"));
    IE2 |= UCA0RXIE;
    DelayGen(1000);
    while(!(If_esp8266_ok())){
        Transmit_UART_Buffer("AT+CIPCLOSE\r\n",(unsigned short)strlen("AT+CIPCLOSE\r\n"));
        IE2 |= UCA0RXIE;
        DelayGen(1000);
    }

    Transmit_UART_Buffer("AT+CIPMUX=0\r\n",(unsigned short)strlen("AT+CIPMUX=0\r\n"));
    IE2 |= UCA0RXIE;
    DelayGen(1000);
    while(!(If_esp8266_ok())){
        Transmit_UART_Buffer("AT+CIPMUX=0\r\n",(unsigned short)strlen("AT+CIPMUX=0\r\n"));
        IE2 |= UCA0RXIE;
        DelayGen(1000);
    }

    unsigned short length = sprintf(tx_buffer,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",Ip,Port);
    Transmit_UART_Buffer(tx_buffer,length);
    IE2 |= UCA0RXIE;
    DelayGen(2000);
    while(!(If_esp8266_ok())){
        Transmit_UART_Buffer(tx_buffer, (unsigned short)length);
        IE2 |= UCA0RXIE;
        DelayGen(2000);
    }
    cleanTXBuffer();
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    if(UART_Rx_Counter<80)
    {
        UART_Rx_Buffer[UART_Rx_Counter]=UCA0RXBUF;//En son alinan 50 karakter verisini diziye yaz.
        if(UART_Rx_Counter > 80){
            //if(UART_Rx_Buffer[UART_Rx_Counter-1]=='O' && UART_Rx_Buffer[UART_Rx_Counter]=='K'){//OK arayan fonksiyon.
            IE2&= ~UCA0RXIE;  //IE2&= ~UCA0RXIE;
            UART_Rx_Counter=0;
            //}
        }
        mode = 1;
    }
    UART_Rx_Counter++;
}

void Init_Timer(void){
    // Use Timer0 A0 for LPM delays
    TA0CTL = TASSEL_2 + TACLR + ID_0 ;  // smclk, clear timer
    TA0CCR0 = 1000;                     //1ms timing
    TA0CCTL0 |= CCIE;                   // Enable capture/compare interrupt for Timer1 A0
}

void DelayGen(int milisecond){
    counter = milisecond;
    TA0CTL |= MC_1;//start timer1 for small delay
    __bis_SR_register(LPM1_bits + GIE);// Sleep during delay
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer1A0Delay(void){
    counter--;
    if(counter == 0){
        TA0CTL &= ~(BIT4 + BIT5);// Delay is complete, disable counting mode
        TA0CTL |= TACLR;// Clear timer for the next usage
        __bic_SR_register_on_exit(LPM1_bits);// wake up
    }
}
