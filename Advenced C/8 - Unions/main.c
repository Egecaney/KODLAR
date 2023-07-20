#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define  TableBufferSize        (int)10
#define  UnionCarBufferSize     (int)20
#define  SoCSecurityBufferSize  (int)20
#define  LeaseCompanyBufferSize (int)40
#define  CarDataBufferSize      (int)40


union Car{
    int     IntValue;
    float   FloatValue;
    char    CharValue[UnionCarBufferSize];
}FirstCar, SecondCar, *ThirdCar;

struct Owner{
    char SoCSecurity[UnionCarBufferSize];
};

struct LeaseCompany{
    char Name[LeaseCompanyBufferSize];
    char HeadQuarters[LeaseCompanyBufferSize];
};

struct CarData{
    char Date[CarDataBufferSize];
    char *Place;
    int  Status;    /** 0 = Owned, 1 = Leased */
    union{
       struct Owner OwnCar;
       struct LeaseCompany LeaseCar;
    };
};

typedef enum ITStatus{
    Reset, Set
};

typedef struct __Table{
    char   *Name;
    enum   ITStatus Status;
    union{
        int     Integer;
        float   Float;
        char    Character;
    }Data;
    union{
        uint32_t UInt32;
        uint16_t UInt16[2];
        uint8_t  UInt8[4];
    }UnsignedData;
}Table;

void SizeOfUnions(union Car FirstCar, union Car SecondCar, union Car *ThirdCar);
void FillTheCarDataStructure(struct CarData *FirstCarData);
void PrintTheCarDataStructure(struct CarData *FirstCarData);
void PrintTheTableStructure(Table *StructTable);

int main(){

    union Car FirstCar, SecondCar, *ThirdCar;
    SizeOfUnions(FirstCar, SecondCar, ThirdCar);

    struct CarData FirstCarData;
    FillTheCarDataStructure(&FirstCarData);

    Table StructTable = {.Name = "Egemen", .Status = Set, .Data.Integer = 100, .UnsignedData.UInt32 = 0x12345678};
    PrintTheTableStructure(&StructTable);

    return 0;
}


void SizeOfUnions(union Car FirstCar, union Car SecondCar, union Car *ThirdCar){
    printf("Memory size occupied by FisrtCar:  %u\n", sizeof(FirstCar));
    printf("Memory size occupied by SecondCar: %u\n", sizeof(SecondCar));
    printf("Memory size occupied by ThirdCar:  %u\n", sizeof(*ThirdCar));
}

void FillTheCarDataStructure(struct CarData *FirstCarData){
    strcpy(FirstCarData->Date, "24/09/1999");
    FirstCarData->Place = " Ankara/Yenimahalle";
    FirstCarData->Status = Set;
    strcpy(FirstCarData->OwnCar.SoCSecurity, "Camera Security");
    strcpy(FirstCarData->LeaseCar.HeadQuarters, "Digital Design Engineer");
    PrintTheCarDataStructure(FirstCarData);

    strcpy(FirstCarData->LeaseCar.Name, "Embedded SW Engineer");
    PrintTheCarDataStructure(FirstCarData);
}

void PrintTheCarDataStructure(struct CarData *FirstCarData){
    printf("\nFirstCarData->Date = %s\n", FirstCarData->Date);
    printf("FirstCarData->Place = %s\n", FirstCarData->Place);
    printf("FirstCarData->Status = %d\n", FirstCarData->Status);
    printf("FirstCarData->OwnCar.SoCSecurity = %s\n", FirstCarData->OwnCar.SoCSecurity);
    printf("FirstCarData->LeaseCar.Name = %s\n", FirstCarData->LeaseCar.Name);
    printf("FirstCarData->LeaseCar.HeadQuarters = %s\n", FirstCarData->LeaseCar.HeadQuarters);
}

void PrintTheTableStructure(Table *StructTable){
    printf("\nStructTable->Name = %s\n", StructTable->Name);
    printf("StructTable->Data.Integer = %d\n", StructTable->Data.Integer);
    printf("StructTable->Data.Float = %lf\n", StructTable->Data.Float);
    printf("StructTable->Data.Character = %c\n", StructTable->Data.Character);
    printf("StructTable->UnsignedData.UInt32    = %x\n", StructTable->UnsignedData.UInt32);
    printf("StructTable->UnsignedData.UInt16[1] = %x\n", StructTable->UnsignedData.UInt16[1]);
    printf("StructTable->UnsignedData.UInt16[0] = %x\n", StructTable->UnsignedData.UInt16[0]);
    printf("StructTable->UnsignedData.UInt8[3]  = %x\n", StructTable->UnsignedData.UInt8[3]);
    printf("StructTable->UnsignedData.UInt8[2]  = %x\n", StructTable->UnsignedData.UInt8[2]);
    printf("StructTable->UnsignedData.UInt8[1]  = %x\n", StructTable->UnsignedData.UInt8[1]);
    printf("StructTable->UnsignedData.UInt8[0]  = %x\n", StructTable->UnsignedData.UInt8[0]);
}


