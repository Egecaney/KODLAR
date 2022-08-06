#include <msp430.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PERIOD 10000      // Samping Period
#define BYTES  20         // Max Number of Bytes Sent on SPI
#define CS_TH  BIT0;      // Set CSB to P2.0 on MCU.

void SetTimer(void);
void SetUART(void);
void SetSPI(void);

uint8_t ReadTHid(void);
void GetCompData(void);
void ReadTHsensor(void);
int32_t CalcTemp(void);
uint32_t CalcHumid(void);
uint32_t CalcPress(void);


// Variables for UART terminal display
char str[80];
volatile uint8_t i,count;
volatile int32_t CorT;
volatile uint32_t CorH, CorP;

// Variables for Reading Data from Sensor
volatile int32_t RawTemp, RawPress, RawHumid;
volatile uint16_t dig_T1, dig_P1;
volatile int16_t  dig_T2, dig_T3;
volatile int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
volatile int32_t t_fine;
volatile uint8_t dig_H1, dig_H3, i;
volatile int8_t dig_H6;
volatile int16_t dig_H2, dig_H4, dig_H5;
volatile unsigned char  Tempbuf[30], Humbuf[15];
char RXBuf[BYTES], RXData[BYTES], TXBuf[BYTES], Data[BYTES];

/*
* FOR SPI:
* P1.5 SCLK (SPI Clock)
* P1.6 MISO (Master In Slave Out)
* P1.7 MOSI (Master Out Slave In)
* P2.0 CS   (Chip Select)
*
* FOR UART:
* P1.1 RXD  (Receiver)
* P1.2 TXD  (Transmitter)
*/

int main(void){

	WDTCTL = WDTPW | WDTHOLD;	// Stop Watchdog Timer
	
    if (CALBC1_1MHZ == 0xFF){   // Check if calibration constant erased
        while(1);               // Do NOT Load Program
    }
	DCOCTL  = 0;                // Select Lowest DCO Settings
	BCSCTL1 = CALBC1_1MHZ;      // Set DCO to 1 MHz
	DCOCTL  = CALDCO_1MHZ;

	//SetTimer();
	SetUART();
	SetSPI();

	//_BIS_SR(GIE);               // Enable Global Interrupts

	volatile uint8_t Flag;
	Flag = ReadTHid();

	 if(Flag);                  // Check for presence of sensor; read its ID code
	 else{                      // Trap CPU and turn on red LED if not found
	     while(1);
	 }

	 GetCompData();             // Get the compensation coefficients from device for raw data conversion

	 while(1){
	     //TA0CCR0 = PERIOD;      // Polling period
	     //LPM3;                  // Wait in Low Power Mode

	     // Burst read on SPI to get 3 press data bytes, 3 temp bytes and 2 humidity bytes
	     ReadTHsensor();

	     // Apply cal factors to Raw Data
	     CorT = CalcTemp();     // Corrected Temperature
	     CorH = CalcHumid();    // Corrected Humidity
	     CorP = CalcPress();    // Corrected Pressure

	     //Send DATA to serial port for display
	     snprintf(str,"%s %lu.%.2lu%s %lu.%.2lu%s %lu.%.2lu%s", "Temperature:", CorT/100, CorT%100,"C Rel Humidity:",CorH/1000, CorH%100,"% Pressure:",CorP/100, CorP%100," hPa\r\n\n");
	     count = sizeof str;
	     for (i=0; i < count; i++){
	         while (!(IFG2 & UCA0TXIFG));    // USCI_A0 TX buffer ready?
	         UCA0TXBUF = str[i];             // Send data 1 byte at a time
	     }
	}
}

/*
#pragma vector = TIMER0_A0_VECTOR
 __interrupt void CCR0_ISR(void){
    LPM3_EXIT;
}*/

void SetTimer(void){
    // Enable the timer interrupt, MC_1 to count up to TA0CCR0, Timer A set to ACLK
    TA0CCTL0 = CCIE;
    TA0CTL |= MC_1 + TASSEL_1;
}

void SetUART(void){

    P1SEL  |= BIT1+BIT2;                // RXD - TXD
    P1SEL2 |= BIT1+BIT2;

    UCA0CTL1 |= UCSSEL_2;               // UART Clock -> SMCLK
    UCA0BR0 = 104;                      // Baud Rate Setting for 1MHz 9600
    UCA0BR1 = 0;                        // Baud Rate Setting for 1MHz 9600
    UCA0MCTL = UCBRS_1;                 // Modulation Setting for 1MHz 9600
    UCA0CTL1 &= ~UCSWRST;               // Initialize UART Module
}

void SetSPI(void){

    UCB0CTL1 |= UCSWRST;                                            // Hold USCI in reset state

    P2DIR  |= BIT0;                                                 // CS
    P2OUT  |= BIT0;
    P1SEL  |= BIT5 + BIT6 + BIT7;                                   // CLK - MISO - MOSI
    P1SEL2 |= BIT5 + BIT6 + BIT7;

    UCB0CTL0 |= UCCKPL + UCCKPH + UCMSB + UCMST + UCSYNC;           // 3-pin, 8-bit, SPI Master
    UCB0CTL1 |= UCSSEL_2;                                           // Clock -> SMCLK
    IFG2 &= ~(UCB0TXIFG+UCB0RXIFG);

    UCB0CTL1 &= ~UCSWRST;                                           // Initialise USCI module

}

uint8_t ReadTHid(void){                  // Get the TH sensor chip ID: 0x60

    volatile int i;
    unsigned char TID[]={0xD0,0x00};     // Read Followed By Dummy Byte

    UCB0CTL1 &= ~UCSWRST;                // Start USCI
    P2OUT &= ~CS_TH;                     // Pull CSB low

    for(i=0;i<sizeof(TID);i++){
        while(!(IFG2 & UCB0TXIFG));      // Check if it is OK to write
        UCB0TXBUF = TID[i];              // Load Data into Transmit Buffer

        while(!(IFG2 & UCB0RXIFG));      // Wait until complete RX Byte is received
        RXBuf[i] = UCB0RXBUF;            // Read Buffer to clear RX Flag
    }

     P2OUT |= CS_TH;                     // Pull CSB line high
     UCB0CTL1 |= UCSWRST;                // Stop USCI

     if(RXBuf[1] == 0x59){
         return  1;
     }
     else{
         return  0;
     }

}

void GetCompData(void){

    /* Compensation data can be read in sleep mode.
     * Use burst read to get temp, pressure, and humidity compensation bytes starting at first data byte 0X88.
     * Retrieve data while CSB is low. */

    UCB0CTL1 &= ~UCSWRST;                // Start USCI
    P2OUT &= ~CS_TH;                     // Pull CSB line low

    while(!(IFG2 & UCB0TXIFG));          // Check if it is OK to write
    UCB0TXBUF = 0x88;                    // Load first address to be read.

    while(!(IFG2 & UCB0RXIFG));          // Wait until complete RX byte is received
    Tempbuf[0] = UCB0RXBUF;              // Read buffer to clear RX flag. The first read byte is of no use

    //Burst mode read of Temperature, Pressure, and first Humidity compensation bytes follows
    for (i=1; i < 27; i++){
        while (!(IFG2 & UCB0TXIFG));
        UCB0TXBUF = 0xAA;                // Load dummy data into transmit buffer

        while (!(IFG2 & UCB0RXIFG));
        Tempbuf[i] = UCB0RXBUF;
    }

    P2OUT |= CS_TH;                      // Pull CSB line high
    UCB0CTL1 |= UCSWRST;                 // Stop USCI

    // Build the temperature compensation coefficients
    dig_T1 = ((uint16_t)(Tempbuf[2] << 8) | (uint16_t)Tempbuf[1]);          //Unsigned 16-bit int
    dig_T2 = (int16_t)((uint16_t)(Tempbuf[4] << 8) | (uint16_t)Tempbuf[3]); //Signed 16-bit int
    dig_T3 = (int16_t)((uint16_t)(Tempbuf[6] << 8) | (uint16_t)Tempbuf[5]); //Signed 16-bit int

    // Build the pressure compensation coefficients
    dig_P1 = ((uint16_t)(Tempbuf[8] << 8) | (uint16_t)Tempbuf[7]);            //Unsigned 16-bit int
    dig_P2 = (int16_t)((uint16_t)(Tempbuf[10] << 8) | (uint16_t)Tempbuf[9]);  //Signed 16-bit int
    dig_P3 = (int16_t)((uint16_t)(Tempbuf[12] << 8) | (uint16_t)Tempbuf[11]); //Signed 16-bit int
    dig_P4 = (int16_t)((uint16_t)(Tempbuf[14] << 8) | (uint16_t)Tempbuf[13]); //Signed 16-bit int
    dig_P5 = (int16_t)((uint16_t)(Tempbuf[16] << 8) | (uint16_t)Tempbuf[15]); //Signed 16-bit int
    dig_P6 = (int16_t)((uint16_t)(Tempbuf[18] << 8) | (uint16_t)Tempbuf[17]); //Signed 16-bit int
    dig_P7 = (int16_t)((uint16_t)(Tempbuf[20] << 8) | (uint16_t)Tempbuf[19]); //Signed 16-bit int
    dig_P8 = (int16_t)((uint16_t)(Tempbuf[22] << 8) | (uint16_t)Tempbuf[21]); //Signed 16-bit int
    dig_P9 = (int16_t)((uint16_t)(Tempbuf[24] << 8) | (uint16_t)Tempbuf[23]); //Signed 16-bit int

    Humbuf[1] = Tempbuf[26];             //This is byte 0xA1

    UCB0CTL1 &= ~UCSWRST; //Start USCI
    P2OUT &= ~CS_TH; //Pull CSB line low

    //Burst read of remaining humidity bytes follows
    while (!(IFG2 & UCB0TXIFG));
    UCB0TXBUF = 0xE1;                    // Load first read address
    while (!(IFG2 & UCB0RXIFG));
    Humbuf[0] = UCB0RXBUF;               // Read buffer to clear RX flag. This byte is of no use

    for(i=2; i < 10; i++){               // Write dummy variable to produce burst read
        while (!(IFG2 & UCB0TXIFG));
        UCB0TXBUF = 0xAA;                // Load dummy data into transmit buffer

        while (!(IFG2 & UCB0RXIFG));
        Humbuf[i] = UCB0RXBUF;
    }

    P2OUT |= CS_TH;                 // Pull CSB line high
    UCB0CTL1 |= UCSWRST;            // Stop USCI

    // Build the humidity compensation coefficients
    dig_H1 = (uint8_t)Humbuf[1];                                          // 0xA1
    dig_H2 = (int16_t)((uint16_t)(Humbuf[3] << 8) | (uint16_t)Humbuf[2]); // 0xE2/0xE1
    dig_H3 = (uint8_t)Humbuf[4];                                          // 0xE3

    //dig_H4 and dig_H5 use the lower and upper nibbles of 0xE5, respectively. Split up Humbuf[6] for this purpose
    dig_H4 = (int16_t)((uint16_t)(Humbuf[5] << 4) | (uint16_t)(Humbuf[6] & 0x0F));       // 0xE4 / low nibble of 0xE5 (12 bits)
    dig_H5 = (int16_t)((uint16_t)(Humbuf[7] << 4) | (uint16_t)((Humbuf[6] >>4) & 0x0F)); // 0xE7 / high nibble of 0xE5 (12 bits)
    dig_H6 = (uint8_t)Humbuf[8];                                                         // 0xE7

}

void ReadTHsensor(void){

    unsigned char TH1[]={0x72,0x01,0x74,0x25,0x75,0x00,0xF7}; // Temp + pressure

    UCB0CTL1 &= ~UCSWRST;        // Start USCI
    P2OUT &= ~CS_TH;             // Pull CSB line low

    //Write above data via SPI.  No useful data is read but save anyway
    for(i=0; i < sizeof TH1; i++){
        while (!(IFG2 & UCB0TXIFG));     // Check if it is OK to write
        UCB0TXBUF = TH1[i];              // Load data into transmit buffer
        while (!(IFG2 & UCB0RXIFG));     // Wait until complete RX byte is received
        RXBuf[i] = UCB0RXBUF;            // Read buffer to clear RX flag. These bytes are of no use
    }

    // Now do a burst read of 8 data bytes (press, temp, humid) from BME280.
    for(i=0; i < 9; i++){
        while (!(IFG2 & UCB0TXIFG));
        UCB0TXBUF = 0xAA;
        while (!(IFG2 & UCB0RXIFG));
        Data[i] = UCB0RXBUF;
    }

    P2OUT |= CS_TH;             // Pull CSB line high
    UCB0CTL1 |= UCSWRST;        // Stop USCI

    /*
    Data[0]:Pressure MSB,  Data[1]:Pressure LSB,  Data[2]:Pressure XLSB
    Data[3]:Temperature MSB, Data[4]:Temperature LSB, Data[5]:Temperature XLSB
    Data[6]:Humidity MSB, Data[7]:Humidity LSB
    Assemble the data bytes to make a 20-bit long integer for pressure and temperature and a 16-bit integer for humidity */
    RawPress = ((uint32_t)Data[0] << 16 | (uint32_t)Data[1] << 8 | Data[2]) >> 4; // 20-bit long unsigned integer
    RawTemp = ((uint32_t)Data[3] << 16 | (uint32_t)Data[4] << 8 | Data[5]) >> 4;  // 20-bit long unsigned integer
    RawHumid = ((uint32_t)Data[6] << 8) | (uint32_t)Data[7];                      // 16-bit unsigned integer
}

// 32-bit integer conversion formula from BME280 spec sheet
int32_t CalcTemp(void){
    volatile int32_t var1, var2, T;
    var1 = (((((int32_t)RawTemp >> 3) - ((int32_t)dig_T1 << 1))) * (int32_t)dig_T2) >> 11;
    var2 = (((int32_t)RawTemp >> 4) - (int32_t)dig_T1);
    var2 = (((var2*var2) >> 12) * (int32_t)dig_T3) >> 14;
    t_fine = var1 + var2;
    T = ((t_fine * 5) + 128) >> 8;
    return T;
}

// Implement integer conversion formula from BME280 spec sheet
uint32_t CalcHumid(void){
    volatile int32_t var3;
    var3 = t_fine - (int32_t)76800;
    var3 = ((((((int32_t)RawHumid << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * var3)) +
        ((int32_t)16384)) >> 15) * (((((((var3 * ((int32_t)dig_H6)) >> 10) * (((var3 *
        ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
        ((int32_t)dig_H2) + (int32_t)8192) >> 14));
    var3 = (var3 - (((((var3 >> 15) * (var3 >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
    if(var3 < 0){
        var3 = 0;
    }
    if(var3 > 419430400){
        var3 = 419430400;
    }
    return (uint32_t)(var3 >> 12);
}

//32-bit integer conversion formula from BME280 spec sheet
uint32_t CalcPress(void){
    volatile int32_t var4, var5;
    volatile uint32_t p;
    var4 = (((int32_t)t_fine)>>1) - (int32_t)0xFA00;
    var5 = (((var4>>2) * (var4>>2)) >> 11 ) * ((int32_t)dig_P6);
    var5 = var5 + ((var4*((int32_t)dig_P5))<<1);
    var5 = (var5>>2)+(((int32_t)dig_P4)<<16);
    var4 = (((dig_P3 * (((var4>>2) * (var4>>2)) >> 13 )) >> 3) + ((((int32_t)dig_P2) * var4)>>1))>>18;
    var4 = ((((0x8000+var4))*((int32_t)dig_P1))>>15);
    if(var4 == 0){
        return 0;             // Avoid exception caused by division by zero
    }
    p = (((uint32_t)(((int32_t)0x100000)-RawPress)-(var5>>12)))*0xC35;
    if(p < 0x80000000){
        p = (p << 1) / ((uint32_t)var4);
    }
    else{
        p = (p / (uint32_t)var4) * 2;
    }
    var4 = (((int32_t)dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
    var5 = (((int32_t)(p>>2)) * ((int32_t)dig_P8))>>13;
    p = (uint32_t)((int32_t)p + ((var4 + var5 + dig_P7) >> 4));
    return p;
}
