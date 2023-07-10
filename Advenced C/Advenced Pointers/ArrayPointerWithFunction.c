#include <stdio.h>
#include <string.h>
#include <stdint.h>

void Func1(uint8_t *Code);
void Func2(uint8_t *SSID);
void I2CFunc(uint8_t *R_Code, uint8_t Size);

int main(void){

    uint8_t  Code[2];
    uint16_t Temp_Code;
    int16_t Data_Valid, Sign;
    int16_t ADC_Code;
    uint8_t R_Code[] = {0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0};

    int16_t LTC2991_VA_Code = 0xABCD;
    uint8_t TX_Buffer[3]; 

    TX_Buffer[0] = 0x05;
    for(int Index = 1; Index < 3; Index++){
        TX_Buffer[Index] = (((uint16_t)LTC2991_VA_Code >> (8*(Index-1))) & 0xFF);
    }

    Func2("\n    -Start 1-");
    Func1(Code);
    printf("%d -- %d -- %d\n", TX_Buffer[0], TX_Buffer[1], TX_Buffer[2]);
    printf("%d -- %d\n", Code[0], Code[1]);

    Temp_Code   = (uint16_t)(Code[0] << 8 | Code[1] << 0);
    Data_Valid  = (int16_t)((Temp_Code >> 15) & 0x0001);
    ADC_Code    = (int16_t)(Temp_Code & 0x7FFFF);
    Sign        = ((ADC_Code & 0x4000) >> 14);

    printf("Temp_Code  : %d\nData_Valid : %d\nADC_Code   :%d\nSign       : %d\n",Temp_Code, Data_Valid, ADC_Code, Sign);

    if(Sign == 1){
        ADC_Code = (ADC_Code ^ 0x7FFF) + 1;
        printf("Negative Sign Value: %d\n", ADC_Code);
    }

    Func2("    -Finish 1-\n");
    Func2("    -Start 2-\n");

    for(int Index = 0; Index < 6; Index++)
        printf("--%d--", *(R_Code + Index));

    I2CFunc(R_Code, (sizeof(R_Code)/sizeof(R_Code[0]))/2);

    for(int Index = 0; Index < 6; Index++)
        printf("--%d--", *(R_Code + Index));

    Func2("\n\n    -Finish 2-");

    return(0);

}


void Func1(uint8_t *Code){
    Code[0] = 0xBD;
    Code[1] = 0x6F;
}

void Func2(uint8_t *SSID){
    printf("%s\n", SSID);
}

void I2CFunc(uint8_t *R_Code, uint8_t Size){
    uint8_t TempValue = 0;
    for(int Index = 0; Index < Size; Index++){
        TempValue = *(R_Code + Index);
        *(R_Code + Index) = *(R_Code + ((Size*2-1) - Index));
        *(R_Code + ((Size*2-1) - Index)) = TempValue;
    }
}
