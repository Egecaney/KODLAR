#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

#define BufferSize  (int)100

void DuringTheNewLine(char Buffer[], int BufSize, char *Return, int SingleCharacter);
bool GetTheCharNumber();
bool WriteTheNotePad();

int main(){

    char Buffer[BufferSize];
    int SingleCharacter = '\0';
    char *Return = NULL;

    DuringTheNewLine(Buffer, BufferSize, Return, SingleCharacter);

    if(GetTheCharNumber() == false)
        exit(1);

    if(WriteTheNotePad() == false)
        exit(1);

    return 0;
}

void DuringTheNewLine(char Buffer[], int BufSize, char *Return, int SingleCharacter){

    /**  char *strchr(const char *str, int c)
         char *fgets(char *str, int n, FILE *stream) */

    if(fgets((Buffer), BufSize, stdin)){
        Return = strchr(Buffer, SingleCharacter);
        if(Return)
            *Return = '\0';
        else
            while((((SingleCharacter = getchar()) != '\n') && (!feof(stdin)) && (!ferror(stdin))));
    }
    else{
        printf("fgets failed, handle error\n");
    }
    printf("Our Buffer contains: %s\n", Buffer);
}

bool GetTheCharNumber(){

    /** size_t getline (char **string, size_t *n, FILE *stream); */

    char    *Buffer = NULL;
    size_t  BufSize = 32;
    size_t  Characters;

    Buffer = (char*)malloc(BufferSize*sizeof(char));

    if(Buffer == NULL)
        return false;

    printf("Type something: ");
    Characters = getline(&Buffer, &BufSize, stdin);

    printf("%u characters were read.\n", Characters);
    printf("You typed : %s\n", Buffer);

    return true;
}

bool WriteTheNotePad(){

    /** int fputs(const char *str, FILE *stream) */

    FILE *FilePtr = NULL;
    FilePtr = fopen("C:\\Users\\canaydugan\\Advanced C\\SEC10_InputAndOutput\\Data.txt", "w");

    if(FilePtr == NULL)
        return false;

    fputs("Hello There, I hope this article will help!", FilePtr);
    fclose(FilePtr);

    return true;
}

