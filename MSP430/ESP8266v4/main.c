#include <msp430.h> 
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

unsigned short UART_Rx_Counter = 0;
char UART_Rx_Buffer[80];
unsigned volatile int counter = 0;
//char tx_buffer[150];

unsigned char Temp_Hum[4] = {10,20,30,40};
//unsigned char DS3231_Data[8] = {0};

uint16_t packetID = 0x01;
uint8_t publishCon = 0x30;
uint8_t subscribeCon = 0x82;
char *protocolName = "MQTT";
uint8_t Qos = 0x00;
int DECsec = 0;
int DECmin = 0;
int DEChour = 0;

void Init_Timer(void);
void Init_UART(void);
void Transmit_UART_Buffer(char *str,unsigned short length);
void Transmit_UART_Char(char c);
unsigned int If_esp8266_ok(void);
void cleanRXBuffer(void);
//void cleanTXBuffer(void);
void ConnectNetwork(char *Ip ,char *Port);
void Connect_IP(char *Ip ,char *Port);
void Connect_Broker(char *clientID, char *ID, char *Password);
void DelayGen(int milisecond);
void publish(char *topic);


int main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    Init_Timer();
    Init_UART();
    ConnectNetwork("Egemen", "69709399ege");
    Connect_IP("iot.ee.hacettepe.edu.tr","1883");
    Connect_Broker("g25eca","g25eca","e737");
    //publish("g32");

    while(1){
        //empty loop
    }
}

void Init_UART(void){
    P1SEL= BIT1 + BIT2; //P1.1 = RXD P1.2=TXD
    P1SEL2= BIT1 + BIT2; // P1.1=RXD & P1.2=TXD
    //UCA0CTL1 |= UCSWRST + UCSSEL_2;
    //UCA0BR0 = 52;  //settings for 19200 baud
    //UCA0BR1 = 0;
    //UCA0MCTL = UCBRS_0;
    UCA0CTL1 |= UCSWRST;
    UCA0CTL0 = 0x00;

    UCA0CTL1 |= UCSSEL_2 | UCSWRST ;

    UCA0MCTL = UCBRF_0 | UCBRS_6;
    UCA0BR0 = 8;
    UCA0BR1 = 00;

    UCA0CTL1 &= ~UCSWRST;

    /*UCA0BR0=104; // BAUDRATE AT 1 MHz 9600
    UCA0BR1=0;//1MHz 9600
    UCA0MCTL= UCBRS0; // MODULATION UCBRSx=1*/

    //UCA0CTL1 &= ~UCSWRST;
    IE2 &= ~UCA0RXIE; // DISABLE VSCI_A0 RX INTERRUPT
    //IE2 |= UCA0RXIE;
}

void Transmit_UART_Buffer(char *str,unsigned short length){
    IE2 &= ~UCA0RXIE;
    unsigned short transmit_counter = 0;
    while(transmit_counter < length){
        Transmit_UART_Char(*str++);
        transmit_counter++;
    }
    IE2 |= UCA0RXIE;
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

    uint8_t TotalLength = 4 + 4 + 6 + 5 + 2 + 5 +2 + 4 +2 ;//32byte

    Transmit_UART_Buffer("AT+CIPSEND=", (unsigned short)strlen("AT+CIPSEND="));
    //Transmit_UART_Char((char)TotalLength);
    //Transmit_UART_Char('2');
    Transmit_UART_Char(TotalLength +'0');
    Transmit_UART_Buffer("\r\n", (unsigned short)strlen("\r\n"));
    DelayGen(100);
    cleanRXBuffer();
/*
    Transmit_UART_Char((char)connect);//1
    Transmit_UART_Char((char)Remainlength);//1
    Transmit_UART_Char((char)(ProtocolNameLength << 8));//1
    Transmit_UART_Char((char)ProtocolNameLength);//1
    Transmit_UART_Buffer(protocolName,(unsigned short)strlen(protocolName));//4
    Transmit_UART_Char((char)level);//1
    Transmit_UART_Char((char)flag);//1
    Transmit_UART_Char((char)(keepAlive << 8));//1
    Transmit_UART_Char((char)keepAlive);//1
    Transmit_UART_Char((char)(ClientIDLength << 8));//1
    Transmit_UART_Char((char)ClientIDLength);//1
    Transmit_UART_Buffer(clientID,(unsigned short)strlen(clientID));//5
    Transmit_UART_Char((char)(IDLength << 8));//1
    Transmit_UART_Char((char)IDLength);//1
    Transmit_UART_Buffer(ID,(unsigned short)strlen(ID));//5
    Transmit_UART_Char((char)(PasswordLength << 8));//1
    Transmit_UART_Char((char)PasswordLength);//1
    Transmit_UART_Buffer(Password,(unsigned short)strlen(Password));//4
    */
    Transmit_UART_Char((char)connect);//1
    Transmit_UART_Char((char)Remainlength);//1
    Transmit_UART_Char((char)(ProtocolNameLength << 8));//1
    Transmit_UART_Char((char)ProtocolNameLength);//1
    Transmit_UART_Buffer(protocolName,(unsigned short)strlen(protocolName));//4
    Transmit_UART_Char((char)level);//1
    Transmit_UART_Char((char)flag);//1
    Transmit_UART_Char((char)(keepAlive << 8));//1
    Transmit_UART_Char((char)keepAlive);//1
    Transmit_UART_Char((char)(ClientIDLength << 8));//1
    Transmit_UART_Char((char)ClientIDLength);//1
    Transmit_UART_Buffer(clientID,(unsigned short)strlen(clientID));//5
    Transmit_UART_Char((char)(IDLength << 8));//1
    Transmit_UART_Char((char)IDLength);//1
    Transmit_UART_Buffer(ID,(unsigned short)strlen(ID));//5
    Transmit_UART_Char((char)(PasswordLength << 8));//1
    Transmit_UART_Char((char)PasswordLength);//1
    Transmit_UART_Buffer(Password,(unsigned short)strlen(Password));//4
    //cleanTXBuffer();
    DelayGen(100);
    cleanRXBuffer();
}

void publish(char *topic)
{
    //cleanTXBuffer();
    uint16_t topiclength = strlen(topic);
    uint8_t remainlength = 2 + topiclength + 13;

    /*unsigned short length = sprintf(tx_buffer,"%c%c%c%c%s%c.%c,%c.%c,%c,%c,%c",(char)publishCon,(char)remainlength,(char)(topiclength << 8),(char)topiclength,topic,Temp_Hum[0],Temp_Hum[1],Temp_Hum[2],Temp_Hum[3],DEChour,DECmin,DECsec);
    sprintf(tx_buffer,"AT+CIPSEND=%d\r\n",length);*/
    //Transmit_UART_Buffer(tx_buffer,length);

    uint8_t TotalLength = 4 + 2 + 13 ;//19 byte

    Transmit_UART_Buffer("AT+CIPSEND=", (unsigned short)strlen("AT+CIPSEND="));
    Transmit_UART_Char((char)TotalLength);
    Transmit_UART_Buffer("\r\n", (unsigned short)strlen("\r\n"));
    //cleanTXBuffer();
    DelayGen(200);

   // sprintf(tx_buffer,"%c%c%c%c%s%c.%c,%c.%c,%c,%c,%c",(char)publishCon,(char)remainlength,(char)(topiclength << 8),(char)topiclength,topic,Temp_Hum[0],Temp_Hum[1],Temp_Hum[2],Temp_Hum[3],DEChour,DECmin,DECsec);
    //Transmit_UART_Buffer(tx_buffer,length);
   // cleanTXBuffer();
    //DelayGen(200);
    Transmit_UART_Char((char)publishCon);//1
    Transmit_UART_Char((char)remainlength);//1
    Transmit_UART_Char((char)(topiclength << 8));//1
    Transmit_UART_Char((char)topiclength);//1
    Transmit_UART_Buffer(topic,(unsigned short)strlen(topic));//2
    Transmit_UART_Char(Temp_Hum[0]);//1
    Transmit_UART_Char('.');//1
    Transmit_UART_Char(Temp_Hum[1]);//1
    Transmit_UART_Char(',');//1
    Transmit_UART_Char(Temp_Hum[2]);//1
    Transmit_UART_Char('.');//1
    Transmit_UART_Char(Temp_Hum[3]);//1
    Transmit_UART_Char(',');//1
    Transmit_UART_Char((char)DEChour);//1DEChour,DECmin,DECsec
    Transmit_UART_Char(':');//1
    Transmit_UART_Char((char)DECmin);//1
    Transmit_UART_Char(':');//1
    Transmit_UART_Char((char)DECsec);//1

    /*
    uint16_t topiclength = strlen(topic);
    uint8_t remainlength = 2+topiclength+strlen(message);

    int length = sprintf(tx_buffer,"%c%c%c%c%s%s",(char)publishCon,(char)remainlength,(char)(topiclength << 8),(char)topiclength,topic,message);
    sprintf(tx_buffer,"AT+CIPSEND=%d\r\n",length);
    Transmit_UART_Buffer(tx_buffer,(unsigned short)length);
    cleanTXBuffer();
    DelayGen(200);

    sprintf(tx_buffer,"%c%c%c%c%s%s",(char)publishCon,(char)remainlength,(char)(topiclength << 8),(char)topiclength,topic,message);
    Transmit_UART_Buffer(tx_buffer, (unsigned short)length);
    cleanTXBuffer();*/
    DelayGen(200);
}
/*
void cleanTXBuffer(void){
    unsigned short i;
    for(i=0;i<150;i++){
        tx_buffer[i] = 0;
    }
}*/

void ConnectNetwork(char *network_id ,char *network_password){
    /*Transmit_UART_Buffer("AT+RST\r\n");
    IE2 |= UCA0RXIE;
    DelayGen(10);
    while(!(If_esp8266_ok())){
        Transmit_UART_Buffer("AT+RST\r\n");
        IE2 |= UCA0RXIE;
        DelayGen(10);
    }*/

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

    /*int length = sprintf(tx_buffer,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",Ip,Port);
    Transmit_UART_Buffer(tx_buffer,(unsigned short)length);
    IE2 |= UCA0RXIE;
    DelayGen(2000);
    while(!(If_esp8266_ok())){
        Transmit_UART_Buffer(tx_buffer, (unsigned short)length);
        IE2 |= UCA0RXIE;
        DelayGen(2000);
    }*/
    Transmit_UART_Buffer("AT+CIPSTART=\"TCP\",\"",(unsigned short)strlen("AT+CIPSTART=\"TCP\",\""));
    Transmit_UART_Buffer(Ip,(unsigned short)strlen(Ip));
    Transmit_UART_Buffer("\",",(unsigned short)strlen("\","));
    Transmit_UART_Buffer(Port,(unsigned short)strlen(Port));
    Transmit_UART_Buffer("\r\n",(unsigned short)strlen("\r\n"));
    IE2 |= UCA0RXIE;
    DelayGen(2000);
    while(!(If_esp8266_ok())){
        Transmit_UART_Buffer("AT+CIPSTART=\"TCP\",\"",(unsigned short)strlen("AT+CIPSTART=\"TCP\",\""));
        Transmit_UART_Buffer(Ip,(unsigned short)strlen(Ip));
        Transmit_UART_Buffer("\",",(unsigned short)strlen("\","));
        Transmit_UART_Buffer(Port,(unsigned short)strlen(Port));
        Transmit_UART_Buffer("\r\n",(unsigned short)strlen("\r\n"));
        IE2 |= UCA0RXIE;
        DelayGen(2000);
    }
    //cleanTXBuffer();
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    if(UART_Rx_Counter<80)
    {
        UART_Rx_Buffer[UART_Rx_Counter]=UCA0RXBUF;//En son alinan 50 karakter verisini diziye yaz.
        if(UART_Rx_Counter > 0){
            if(UART_Rx_Buffer[UART_Rx_Counter-1]=='O' && UART_Rx_Buffer[UART_Rx_Counter]=='K'){//OK arayan fonksiyon.
                IE2&= ~UCA0RXIE;
                UART_Rx_Counter=0;
            }
        }
    }
    UART_Rx_Counter++;
}

void Init_Timer(void){
    // Use Timer0 A0 for LPM delays
    TA0CTL = TASSEL_2 + TACLR + ID_0 ;// smclk, clear timer
    TA0CCR0 = 1000-1;//1ms timing
    TA0CCTL0 |= CCIE;// Enable capture/compare interrupt for Timer1 A0
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
        __bic_SR_register_on_exit(CPUOFF);// wake up
        //IE2 &= ~UCA0RXIE;
    }
}
