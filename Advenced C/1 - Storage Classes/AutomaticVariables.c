#include "main.h"

/*
 * Automatic Storage is means of conserving memory
 *     - Automatic variables exist only when they are needed
 *     - They are created when the function in which they are defined is entered
 * 	   - They are destroyed when the function is exited
 */

int AutoFunction();
char *myFunction();

int AutoFunction(){

    auto int opengenus_function();
    
    int opengenus_function(int Index){
        int b = Index;
        printf("%d.", b);
    }

	for(int Index=0; Index<10; Index++){
        opengenus_function(Index);
		printf(" Index: %d\n", Index);
	}

	// char *myName = myFunction();
	printf("%s\n", myFunction());
    
}

char *myFunction(){
	return("Egemen Can AYDUGAN");
}

