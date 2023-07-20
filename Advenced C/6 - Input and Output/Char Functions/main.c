#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void convertCase(FILE *FilePtr, const char *TXTFilePath);

int main(void){

    /** File pointer to hold reference of input file */
    FILE *FilePtr = NULL;
    char *TXTFilePath = "C:\\Users\\canaydugan\\Advanced C\\SEC10_InputAndOutput\\Data.txt";

    printf("Path of source file is ./Data.txt ");
    FilePtr = fopen(TXTFilePath, "r");

     /** fopen() return NULL if unable to open file in given mode. */
    if (FilePtr == NULL){
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read privilege.\n");
        exit(EXIT_FAILURE);
    }

    convertCase(FilePtr, TXTFilePath);

    return 0;
}

void convertCase(FILE *FilePtr, const char *TXTFilePath){

    FILE *Destiny = NULL;
    char Character = '\0';
    int NumberOfWord = 1, NumberOfCharacter = 1;

    /** Temporary file to store result */
    Destiny = fopen("temp.txt", "w");

    /** If unable to create temporary file */
    if (Destiny == NULL){
        printf("Unable to create temporary file.");
        fclose(FilePtr);
        exit(EXIT_FAILURE);
    }

    /** Repeat till end of file. */
    while ((Character = fgetc(FilePtr)) != EOF){
        /** If current character is uppercase then toggle it to lowercase and vice versa. */
        if (isupper(Character))
            Character = tolower(Character);
        else if (islower(Character))
            Character = toupper(Character);

        if((Character == ' ') || (Character == '\n'))
            NumberOfWord++;
        else
            NumberOfCharacter++;

        /** Print toggled character to destination file.*/
        fputc(Character, Destiny);
    }

    /** Close all files to release resource */
    fclose(FilePtr);
    fclose(Destiny);

    /** Delete original source file */
    remove(TXTFilePath);

    /** Rename temporary file as original file */
    rename("Temp.txt", TXTFilePath);

    printf("\nThe number of words in the file are : %d\n", NumberOfWord);
    printf(" The number of characters in the file is : %d\n\n", NumberOfCharacter);

}

