#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define StringBufferSize        255
#define MinStringBufferSize     10

void Function_SPRINTF();
bool Function_FPRINTF();
bool Function_FSCANF();
void Function_SSCANF();

bool CHALLENGE();
int  isEven(const int);
int  isPrime(const int);

int main(){

    Function_SPRINTF();

    /* The reason it prints "Number number 10" 2 times is Windows OS. Linux does not print 2 times. */
    if(Function_FPRINTF() != true)
        exit(EXIT_FAILURE);

    if(Function_FSCANF() != true)
        exit(EXIT_FAILURE);

    Function_SSCANF();

    if(CHALLENGE() != true)
        exit(EXIT_FAILURE);

    return 0;
}

void Function_SPRINTF(){
    char String[StringBufferSize];
    int FirstNumber = 10, SecondNumber = 20, Summation = FirstNumber + SecondNumber;
    sprintf(String, "Summation of %d and %d is %d\n", FirstNumber, SecondNumber, Summation);
    puts(String);
}

bool Function_FPRINTF(){
    FILE *FilePointer = NULL;
    char *TXTFilePath = "Numbers.txt";
    char String[StringBufferSize];

    /* Open the file for read and write operation */
    if((FilePointer = fopen(TXTFilePath,"r+")) == NULL){
        printf("Cannot open the file...\n");
        return(false);
    }

    for(int Index = 0; Index < 10; Index++){
        /* Enter the strings with values in the file */
        fprintf(FilePointer, "The count number is %d\n", Index+1);
    }

    fclose(FilePointer);

    if((FilePointer = fopen(TXTFilePath,"r+")) == NULL){
        printf("Cannot open the file...\n");
        return(false);
    }

    printf("File content is --\n");
    printf("\n.......PRINT THE STRINGS.......\n\n");

    while(!feof(FilePointer)){
        fgets(String, StringBufferSize, FilePointer);
        printf("%s", String);
    }

    fclose(FilePointer);
    return(true);
}

bool Function_FSCANF(){
    FILE *FilePointer = NULL;
    char *TXTFilePath = "Numbers.txt";
    char String[StringBufferSize];

    /* a+ mode allows the program to both read and write in the file. */
    if((FilePointer = fopen(TXTFilePath,"a+")) == NULL){
        fprintf(stdout, "Cannot open the file.\n");
        return(false);
    }

    puts("\nEnter words to add to the file; press the #");
    puts("key at the beginning of a line to terminate.");
    while((fscanf(stdin, "%40s", String) == 1) && (String[0] != '#')){
        fprintf(FilePointer, "%s\n", String);
    }

    puts("File contents:");
    rewind(FilePointer);    /* Go back the beginning of file */

    while((fscanf(FilePointer, "%40s", String) == 1)){
        puts(String);
    }

    puts("Done!");
    if(fclose(FilePointer) != 0)
        fprintf(stderr, "Error closing file\n");

    return(true);
}

void Function_SSCANF(){
    char *String = "Egemen Can Aydugan 24 September 1999";
    char FirstName[MinStringBufferSize], SecondName[MinStringBufferSize], Surname[MinStringBufferSize], Month[MinStringBufferSize];
    int  Day = 0, Year = 0, Ret = 0;

    Ret = sscanf(String, "%s %s %s %d %s %d", FirstName, SecondName, Surname, &Day, Month, &Year);
    printf("\nName: %s %s\nSurname: %s\nDay/Month/Year: %d %s %d\nRet: %d\n", FirstName, SecondName, Surname, Day, Month, Year, Ret);

    String = "Emre Aydugan 04 November 1993";
    Ret = sscanf(String, "%s %s %d %s %d", FirstName, Surname, &Day, Month, &Year);
    printf("\nName: %s\nSurname: %s\nDay/Month/Year: %d %s %d\nRet: %d\n", FirstName, Surname, Day, Month, Year, Ret);
}

bool CHALLENGE(){

    FILE *FilePointer = NULL;
    int Number = 0, Success = 0;
    FilePointer   = fopen("ChallengeNumbers.txt", "r");

    if(FilePointer == NULL){
        /* Unable to open file hence exit */
        printf("Unable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return false;
    }

    /* File open success message */
    printf("File opened successfully. Reading integers from file. \n\n");
    // Read an integer and store read status in success. (initial read)
    Success = fscanf(FilePointer, "%d", &Number);

    do{
        if (isPrime(Number))
            printf("Prime number found: %d\n", Number);
        else if (isEven(Number))
            printf("Even number found: %d\n", Number);
        else
           printf("Odd number found: %d\n", Number);

        // Read an integer and store read status in success.
        Success = fscanf(FilePointer, "%d", &Number);

    }while(Success != -1);

    fclose(FilePointer);
    return true;
}

/* Check whether a given number is even or not. The function return 1 if given number is odd, otherwise return 0. */
int isEven(const int num){
    return !(num & 1);
}

/* Check whether a number is prime or not. Returns 1 if the number is prime otherwise 0. */
int isPrime(const int num){
    int i = 0;;

    /* Only positive integers are prime */
    if(num < 0)
        return 0;

    for ( i=2; i<=num/2; i++ ){
        /* If the number is divisible by any number other than 1 and self then it is not prime */
        if (num % i == 0){
            return 0;
        }
    }

    return 1;
}
