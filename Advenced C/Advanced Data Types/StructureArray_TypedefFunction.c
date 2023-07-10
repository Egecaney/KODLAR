#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StructureArray_TypedefFunction.h"

ProductFunctionPtr Products = &ProductResult;
FunctionFunc HelloThere = &doSomething;

ProductValues Market1, Market2;
ClientTest ClientTestArray[NumberOfTest + 1] = {{"", NULL, 0, 0 },
                                                {"Market 1", (FunctionFunc)StartTest1, CONTROL_BOARD_TEST, TEST_NOT_PERFORMED },
                                                {"Market 2", (FunctionFunc)StartTest2, CONTROL_BOARD_TEST, TEST_NOT_PERFORMED }};

int main(void){
    HelloThere();

    ClientTestArray[FirstTestNameIndex].Test_Type = CONTROL_BOARD_TEST;
    StartTest1();
    ClientTestArray[SecondTestNameIndex].Test_Type = HIDE_TEST;
    StartTest2();

    return(0);
}

void doSomething(void) { printf("\nHello There!\n"); }

void StartTest1(void){
    if(ClientTestArray[FirstTestNameIndex].Test_Type == CONTROL_BOARD_TEST){
        GetResults(ClientTestArray[FirstTestNameIndex].Test_Name, &Market1);
        ClientTestArray[FirstTestNameIndex].Test_Result = Market1_ControlTest(Market1.FirstProduct, Market1.SecondProduct);
    }
    else{
        printf("\nWrong Test Type for %s!", ClientTestArray[FirstTestNameIndex].Test_Name);
    }
}

void StartTest2(void){
    if(ClientTestArray[SecondTestNameIndex].Test_Type == CONTROL_BOARD_TEST){
        GetResults(ClientTestArray[SecondTestNameIndex].Test_Name, &Market2);
        ClientTestArray[SecondTestNameIndex].Test_Result = Market2_ControlTest(Market2.FirstProduct, Market2.SecondProduct);
    }
    else{
        printf("\nWrong Test Type for %s!", ClientTestArray[SecondTestNameIndex].Test_Name);
    }
}

void GetResults(char* Market, ProductValues *ProductV){
    printf("\nFor %s:\nEnter the number of Product1: ", Market);
    scanf("%d", &(ProductV->FirstProduct));
    printf("Enter the number of Product2: ", Market);
    scanf("%d", &(ProductV->SecondProduct));
}

int ProductResult(int FirstProduct, int SecondProduct){
  return FirstProduct*SecondProduct;
}

TestResult Market1_ControlTest(int FirstProduct, int SecondProduct){
    TestResult  ReturnOfResult;
    int ResultOfProducts = (*Products)(FirstProduct, SecondProduct);
    printf("Total Product: %d\n", ResultOfProducts);

    if(ResultOfProducts > MaxLevelOfProductResultForMarket1)
        ReturnOfResult = RETURN_GOOD;
    else if(ResultOfProducts >= MinLevelOfProductResultForMarket1 || ResultOfProducts <= MaxLevelOfProductResultForMarket1)
        ReturnOfResult = RETURN_ENOUGH;
    else
        ReturnOfResult = RETURN_BAD;

    return ReturnOfResult;
}

TestResult Market2_ControlTest(int FirstProduct, int SecondProduct){
    TestResult  ReturnOfResult;
    int ResultOfProducts = (*Products)(FirstProduct, SecondProduct);
    printf("Total Product: %d\n", ResultOfProducts);

    if(ResultOfProducts > MaxLevelOfProductResultForMarket2)
        ReturnOfResult = RETURN_GOOD;
    else if(ResultOfProducts >= MinLevelOfProductResultForMarket2 || ResultOfProducts <= MaxLevelOfProductResultForMarket2)
        ReturnOfResult = RETURN_ENOUGH;
    else
        ReturnOfResult = RETURN_BAD;

    return ReturnOfResult;
}