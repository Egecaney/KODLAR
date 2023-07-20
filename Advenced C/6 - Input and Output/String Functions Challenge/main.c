#include <stdio.h>
#include <stdlib.h>

#define BUF 256

int HasCharacters(char ch, const char * line);

int main(int argc, char *argv[]){

   FILE *FilePointer = NULL;
   char Character    = '\0';
   char Line[BUF];

   if(argc != 3) {
      printf("Usage: %s character filename\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   Character = argv[1][0];

   if((FilePointer = fopen(argv[2], "r")) == NULL){
      printf("Can't open %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   while(fgets(Line, BUF, FilePointer) != NULL){
      if(HasCharacters(Character, Line))
         fputs(Line, stdout);
   }

   fclose(FilePointer);
   return 0;
}

int HasCharacters(char Character, const char * Line) {
    while(*Line)
        if(Character == *Line++)
            return 1;

    return 0;
}

/** Project -> Set Program's Arguments -> Debug and X Data.txt -> Build&Run */
