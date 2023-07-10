
/* DEFINE AND TYPEDEF */
#define TestNameBufferSize  (int)100
#define NumberOfTest        (int)2

#define MaxLevelOfProductResultForMarket1    (int)50000
#define MinLevelOfProductResultForMarket1    (int)25000

#define MaxLevelOfProductResultForMarket2    (int)20000
#define MinLevelOfProductResultForMarket2    (int)10000

#define FirstTestNameIndex      (int)1
#define SecondTestNameIndex     (int)2

typedef int (*ProductFunctionPtr)(int,int);
typedef void (*FunctionFunc)();

/* ENUM */
typedef enum{
    TEST_NOT_PERFORMED,
    TEST_SUCCEEDED,
    TEST_FAILED
}TestResult;

typedef enum{
    RETURN_BAD = -1,
    RETURN_GOOD = 0,
    RETURN_ENOUGH = 1,
}ReturnType;

typedef enum{
    HIDE_TEST,
    DEVICE_TEST,
    CONTROL_BOARD_TEST
}TestType;

typedef struct __ProductValues{
	int 	FirstProduct;
    int 	SecondProduct;
}ProductValues;

/* STRUCT */
typedef struct{
    char Test_Name[TestNameBufferSize];
    FunctionFunc Function;
    int  Test_Type;
    int  Test_Result;
}ClientTest;

/* FUNCTİON */
void StartTest1(void);
void StartTest2(void);
void doSomething(void);
int ProductResult(int FirstProduct, int SecondProduct);
TestResult Market1_ControlTest(int FirstProduct, int SecondProduct);
TestResult Market2_ControlTest(int FirstProduct, int SecondProduct);
void GetResults(char* Market, ProductValues *ProductV);